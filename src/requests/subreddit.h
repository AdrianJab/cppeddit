#pragma once

#include "baserequester.h"

#include "reddit/implementations.h"
#include "reddit/interfaces.h"

#include <cpr/cpr.h>

#include <memory>

namespace Cppeddit {
	namespace Requesters {
		class Subreddit : public BaseRequester {
		public:
			Subreddit(std::shared_ptr<BaseAuthoriser> authoriser, const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent);

			std::unique_ptr<Interfaces::Listing> request_listing(Implementations::Subreddit::Listings type);
		private:
			cpr::Response send_request(const std::string&& token);
		};
	}
}
