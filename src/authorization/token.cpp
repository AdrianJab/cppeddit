#include "token.h";

#include <iostream>
#include <iomanip>

namespace Cppeddit {
	std::string Token::get_name() const {
		return m_access_token;
	}

	std::string Token::get_expiration_date() const
	{
		auto tt = Clock::to_time_t(m_end_date);
		auto tm = *std::localtime(&tt);
		std::stringstream ss;
		ss << std::put_time(&tm, "%d.%m.%y %H:%M:%S");
		return ss.str();
	}

	bool Token::is_valid() const {
		return Clock::now() > m_end_date;
	}

	bool Token::expired() const
	{
		return !is_valid();
	}

	Token* Token::from_json(Json::Value&& json) {
		std::string token = json.get("access_token", "").asString();
		int seconds = json.get("expires_in", 0).asInt();
		std::string scope = json.get("scope", "").asString();
		std::string bearer = json.get("bearer", "").asString();

		if (token.empty() || seconds == 0)
			throw bad_token_data(json);

		return new Token(token, seconds, scope, bearer);
	}

	Token::Token(const std::string& id, int sec, const std::string& scope, const std::string& type)
		: m_access_token(id),
		m_expires_seconds(sec),
		m_scope(scope),
		m_token_type(type)
	{
		m_start_date = TimePoint{ Clock::now() };
		m_end_date = m_start_date + Seconds{ sec };
	}

	bad_token_data::bad_token_data(const Json::Value& bad_json)
		: std::exception((std::string("Invalid token data received. Cannot create token from data: ") + bad_json.toStyledString()).c_str())
	{
	}

}
