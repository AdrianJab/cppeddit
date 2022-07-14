#include "client.h"

#include "authorization/credidentials.h"
#include "authorization/scriptauthoriser.h"
#include "requests/subreddit.h"

namespace Cppeddit {
	Client::Client(
		AppType type,
		const std::string& client_id,
		const std::string& client_secret,
		const std::string& username,
		const std::string& password,
		const std::string& user_agent)
	{
		Credidentials client{ client_id, client_secret };
		Credidentials user{ username, password };

		switch (type)
		{
		case Cppeddit::AppType::WebApp:
			//Todo
			break;
		case Cppeddit::AppType::InstalledApp:
			//Todo
			break;
		case Cppeddit::AppType::Script:
			m_authoriser = std::make_shared<ScriptAuthoriser>(client, user, user_agent);
			break;
		default:
			break;
		}

		//Getting the authorisation token from reddit API
		m_authoriser->authorise();

		m_subreddits = std::make_unique<Requesters::Subreddit>(
				m_authoriser,
				client,
				user,
				user_agent);

		subreddit("funny_animals");
	}

	void Client::subreddit(const std::string& name)
	{
		using Posts = Implementations::Subreddit::Listings;
		m_subreddits->request_listing(Posts::Hot);
	}

}
