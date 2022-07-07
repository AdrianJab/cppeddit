#include "scriptauthoriser.h"
#include "globals.h"

#include <iostream>
#include <memory>

namespace Cppeddit {
	ScriptAuthoriser::ScriptAuthoriser(const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent)
		: BaseAuthoriser(client_data, user_data, user_agent)
	{
	}

	void ScriptAuthoriser::authorise()
	{
		//we need to get new token only if the onle one expired
		//or we haven't got one yet
		if (!m_current_token) {
			request_token();
			return;
		}

		if (!m_current_token->is_valid()) {
			refresh_token();
		}
	}

	void ScriptAuthoriser::request_token()
	{
		auto r = send_request("password");

		//token received
		if (r.status_code == 200) {
			m_last_token_type = "password";

			Json::Value data;
			m_reader.parse(r.text, data);
			m_current_token = std::unique_ptr<Token>(Token::from_json(std::move(data)));

			std::cout << "Token received " << m_current_token->get_name() << " Valid until: "
				<< m_current_token->get_expiration_date() << std::endl;
		}
	}

	void ScriptAuthoriser::refresh_token()
	{
		auto r = send_request("refresh_token");

		//token refreshed
		if (r.status_code == 200) {
			m_last_token_type = "access_token";

			Json::Value data;
			m_reader.parse(r.text, data);
			m_current_token = std::unique_ptr<Token>(Token::from_json(std::move(data)));

			std::cout << "Token refreshed " << m_current_token->get_name() << " Valid until: "
				<< m_current_token->get_expiration_date() << std::endl;
		}
	}

	void ScriptAuthoriser::revoke_token()
	{
		if (m_current_token) {
			auto r = send_revoke_request();

			//token revoked
			if (r.status_code == 200) {
				m_last_token_type = "";
				m_current_token.reset();

				std::cout << "Current token succesfully revoked" << std::endl;
			}
		}
			
	}

	cpr::Response ScriptAuthoriser::send_request(const std::string& grant_type)
	{
		auto auth = cpr::Authentication{ m_client_data.name, m_client_data.password };
		auto payload = cpr::Payload{
			{"grant_type", grant_type},
			{"username", m_user_data.name},
			{"password", m_user_data.password}
		};
		auto headers = cpr::Header{ {"User-Agent", m_user_agent} };
		cpr::Response r = cpr::Post(
			cpr::Url{ REDDIT_TOKEN_ACCESS },
			auth,
			payload,
			headers
		);

		std::cout << "Received response from " << REDDIT_TOKEN_ACCESS << ", status code: "
			<< r.status_code << ", payload: " << r.text << std::endl;

		return r;
	}
	cpr::Response ScriptAuthoriser::send_revoke_request()
	{
		auto auth = cpr::Authentication{ m_client_data.name, m_client_data.password };
		auto payload = cpr::Payload{
			{"token", m_current_token->get_name()},
			{"token_type_hint", m_last_token_type}
		};
		auto headers = cpr::Header{ {"User-Agent", m_user_agent} };
		cpr::Response r = cpr::Post(
			cpr::Url{ REDDIT_TOKEN_REVOKE },
			auth,
			payload,
			headers
		);

		std::cout << "Received revoke response from " << REDDIT_TOKEN_REVOKE << ", status code: "
			<< r.status_code << ", payload: " << r.text << std::endl;

		return r;
	}
}