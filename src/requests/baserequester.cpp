#include "baserequester.h"

#include "authorization/scriptauthoriser.h"

namespace Cppeddit {
	namespace Requesters {
		BaseRequester::BaseRequester(std::shared_ptr<BaseAuthoriser> authoriser, const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent)
			: m_client(client_data),
			m_user(user_data),
			m_agent(user_agent),
			m_authoriser(authoriser)
		{
		}
	}
}
