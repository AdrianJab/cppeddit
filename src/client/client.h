#pragma once
#include "authorization/baseauthoriser.h"
#include "requests/subreddit.h"

#include <memory>
#include <string>

namespace Cppeddit {
	enum class AppType {
		WebApp,
		InstalledApp,
		Script
	};

	class Client {
	public:
		Client(
			AppType type,
			const std::string& client_id,
			const std::string& client_secret,
			const std::string& username,
			const std::string& password,
			const std::string& user_agent
		);

		void subreddit(const std::string& name);
	private:
		std::shared_ptr<BaseAuthoriser> m_authoriser;
		//Don't need polymorphism here
		std::unique_ptr<Requesters::Subreddit> m_subreddits;
	};
}