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
				Put,
				Post
			};

			Type type;
			cpr::Authentication authentication;
			cpr::Header headers;
			cpr::Payload payload;
		};

		class Client {
		public:
			Client(const std::string& address);

			bool send(const RequestData& request);
			bool send(const RequestData& request, std::function<void(const std::string&)> callback);
		private:
			bool handle_response(const cpr::Response& resp);
			cpr::Response get_response(const RequestData& request);

			const std::string& m_address;
		};
	}
}