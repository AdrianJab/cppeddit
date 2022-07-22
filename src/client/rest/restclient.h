#pragma once

#include <cpr/cpr.h>

#include <string>
#include <vector>
#include <functional>

namespace Cppeddit {
	namespace Rest {
		struct RequestData {
			enum Type {
				Get,
				Put
			};

			Type type;
			cpr::Authentication authentication;
			cpr::Header headers;
			cpr::Payload payload;
		};

		class Client {
		public:
			Client(const std::string& address);

			void send(const RequestData& request);

			void register_success_callback(std::function<void(const std::string&)> c);
			void register_failure_callback(std::function<void(const std::string&)> c);
		private:
			void handle_response(const cpr::Response& resp);

			std::vector<std::function<void(const std::string&)>> m_success_callbacks;
			std::vector<std::function<void(const std::string&)>> m_failure_callbacks;
			const std::string& m_address;
		};
	}
}