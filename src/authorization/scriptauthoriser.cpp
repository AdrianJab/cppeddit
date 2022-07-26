#include "scriptauthoriser.h"
#include "globals.h"

#include <iostream>
#include <memory>

namespace Cppeddit {
	ScriptAuthoriser::ScriptAuthoriser(const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent)
		: m_client{ REDDIT_TOKEN_ACCESS }, BaseAuthoriser(client_data, user_data, user_agent)
	{
	}

	std::string ScriptAuthoriser::authorise()
	{
		//we need to get new token only if the onle one expired
		//or we haven't got one yet
		if (!m_current_token) {
			request_token();
		} else if (!m_current_token->is_valid()) {
			refresh_token();
		}

		return m_current_token ? m_current_token->get_name() : "";
	}

	void ScriptAuthoriser::request_token()
	{
		auto payload = cpr::Payload{
			{"grant_type", "password"},
			{"username", m_user_data.name},
			{"password", m_user_data.password}
		};
		Rest::RequestData rq{ make_request(payload) };

		auto callback = std::bind(&ScriptAuthoriser::generate_token, this, std::placeholders::_1);
		m_client.send(rq, callback);
	}

	void ScriptAuthoriser::refresh_token()
	{
		auto payload = cpr::Payload{
			{"grant_type", "refresh_token"},
			{"username", m_user_data.name},
			{"password", m_user_data.password}
		};
		Rest::RequestData rq{ make_request(payload) };

		auto callback = std::bind(&ScriptAuthoriser::generate_token, this, std::placeholders::_1);
		m_client.send(rq, callback);
	}

	void ScriptAuthoriser::revoke_token()
	{
		if (m_current_token) {
			auto payload = cpr::Payload{
				{"token", m_current_token->get_name()},
				{"token_type_hint", m_last_token_type}
			};
			Rest::RequestData rq{ make_request(payload) };

			//For now we dont wait for revocation resposne (TODO in future handle this case)
			auto ok = m_client.send(rq);

			if (ok) {
				m_last_token_type = "";
				m_current_token.reset();
				std::cout << "Current token succesfully revoked" << std::endl;
			}
		}
	}

	void ScriptAuthoriser::generate_token(const std::string& payload)
	{
		Json::Value data;
		m_reader.parse(payload, data);

		BaseAuthoriser::load_token(std::move(data));

		//The creation of token may fail
		if (m_current_token) {
			m_last_token_type = "access_token";

			std::cout << "Token received " << m_current_token->get_name() << " Valid until: "
				<< m_current_token->get_expiration_date() << std::endl;
		}
	}
	Rest::RequestData ScriptAuthoriser::make_request(const cpr::Payload& payload) const
	{
		auto auth = cpr::Authentication{ m_client_data.name, m_client_data.password };
		auto headers = cpr::Header{ {"User-Agent", m_user_agent} };
		return Rest::RequestData{ Rest::RequestData::Post, auth, headers, payload };
	}
}