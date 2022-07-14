#pragma once

#include "authorization/credidentials.h"
#include "reddit/interfaces.h"
#include "authorization/baseauthoriser.h"

#include <memory>

namespace Cppeddit {
	namespace Requesters {
		class BaseRequester {
		protected:
			BaseRequester(std::shared_ptr<BaseAuthoriser> authoriser, const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent);

			const Credidentials m_client;
			const Credidentials m_user;
			const std::string m_agent;

			std::shared_ptr<BaseAuthoriser> m_authoriser;
		};
	}
}