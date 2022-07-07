#pragma once
#include <chrono>
#include <ctime>
#include <string>
#include <jsoncpp/json/json.h>

namespace Cppeddit {

	using namespace std::chrono_literals;

	using Clock = std::chrono::system_clock;
	using Seconds = std::chrono::seconds;

	using TimePoint = std::chrono::time_point<Clock>;

	class bad_token_data : public std::exception {
	public:
		bad_token_data(const Json::Value& bad_json);
	};

	class Token {
	public:
		std::string get_name() const;
		std::string get_expiration_date() const;

		bool is_valid() const;
		bool expired() const;

		static Token* from_json(Json::Value&& json);
	private:
		Token(const std::string& id, int sec, const std::string& scope = "", const std::string& type = "");

		std::string m_access_token;
		TimePoint m_start_date;
		TimePoint m_end_date;
		int m_expires_seconds;
		std::string m_scope;
		std::string m_token_type;
	};

}