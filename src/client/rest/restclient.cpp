#include "restclient.h"

#include <iostream>

namespace Cppeddit {
	namespace Rest {
		Client::Client(const std::string& address) : m_address(address)
		{
		}

		bool Client::send(const RequestData& request)
		{
			auto resp = get_response(request);
			return handle_response(resp);
		}

		bool Client::send(const RequestData& request, std::function<void(const std::string&)> callback)
		{
			auto resp = get_response(request);
			auto ok = handle_response(resp);
			if (ok) callback(resp.text);
			return ok;
		}

		bool Client::handle_response(const cpr::Response& resp)
		{
			if (resp.status_code != 200) {
				std::cout << "Received bad rest code from " << m_address << " code: " << resp.status_code
					<< " reason: " << resp.reason;
				return false;
			}

			if (resp.error) {
				std::cout << "Received error from " << m_address << "error: " << resp.error.message << "(" << static_cast<int>(resp.error.code) << ")"
					<< std::endl;
				return false;
			}

			return true;
		}
		cpr::Response Client::get_response(const RequestData& request)
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
			case RequestData::Type::Post:
				resp = cpr::Post(
					cpr::Url{ m_address },
					request.authentication,
					request.headers,
					request.payload);
				break;
			default:
				break;
			}
			return resp;
		}
	}
}