#include "restclient.h"

#include <iostream>

namespace Cppeddit {
	namespace Rest {
		Client::Client(const std::string& address) : m_address(address)
		{
		}
		void Client::send(const RequestData& request)
		{
			cpr::Response resp;
			switch (request.type)
			{
			case RequestData::Type::Get:
				resp = cpr::Get(
					cpr::Url{ m_address },
					request.authentication,
					request.headers,
					request.payload);
				break;
			case RequestData::Type::Put:
				resp = cpr::Put(
					cpr::Url{ m_address },
					request.authentication,
					request.headers,
					request.payload);
				break;
			default:
				break;
			}
			handle_response(resp);
		}
		void Client::register_success_callback(std::function<void(const std::string&)> c)
		{
			m_success_callbacks.push_back(c);
		}
		void Client::register_failure_callback(std::function<void(const std::string&)> c)
		{
			m_failure_callbacks.push_back(c);
		}
		void Client::handle_response(const cpr::Response& resp)
		{
			//TODO implement
			auto invoked_container = m_success_callbacks;

			if (resp.status_code != 200) {
				invoked_container = m_failure_callbacks;

				std::cout << "Received bad rest code from " << m_address << " code: " << resp.status_code
					<< " reason: " << resp.reason;
			}

			if (resp.error) {
				invoked_container = m_failure_callbacks;

				std::cout << "Received error from " << m_address << "error: " << resp.error.message << "(" << static_cast<int>(resp.error.code) << ")"
					<< std::endl;
			}

			for (const auto& f : invoked_container) {
				f(resp.text);
			}

		}
	}
}