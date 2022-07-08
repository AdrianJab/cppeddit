#pragma once
#include "authorization/baseauthoriser.h"

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
		std::unique_ptr<BaseAuthoriser> m_authoriser;
	};
}