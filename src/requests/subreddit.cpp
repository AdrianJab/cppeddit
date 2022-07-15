#include "subreddit.h"
#include "globals.h"

#include "reddit/deserialiser.h"

#include <iostream>

namespace Cppeddit {
	namespace Requesters {
		Subreddit::Subreddit(std::shared_ptr<BaseAuthoriser> authoriser, const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent)
			: BaseRequester{authoriser, client_data, user_data, user_agent}
		{
		}

		Interfaces::Listing Subreddit::request_listing(Implementations::Subreddit::Listings type)
		{
			auto data = send_request(m_authoriser->authorise()).text;

			auto t = Deserialisation::make_listing(data);

			return t;
		}

		cpr::Response Subreddit::send_request(const std::string&& token)
		{
			const std::string url = REDDIT_API_BASE + "/r/funny";
			const std::string bearer = "bearer " + token;
			auto auth = cpr::Authentication{ m_client.name, m_client.password };
			auto headers = cpr::Header{ {"User-Agent", m_agent}, {"Authorization", bearer} };
			cpr::Response r = cpr::Get(
				cpr::Url{ url },
				auth,
				headers
			);

			std::cout << "Received hot posts from " << url << ", status code: "
				<< r.status_code << ", payload: " << r.text << std::endl;

			return r;
		}
	}
}