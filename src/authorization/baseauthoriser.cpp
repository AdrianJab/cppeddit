#include "baseauthoriser.h"

namespace Cppeddit {

	bool BaseAuthoriser::active() const
	{
		return m_current_token->is_valid();
	}

	BaseAuthoriser::BaseAuthoriser(const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent)
		: m_client_data(client_data),
		m_user_data(user_data),
		m_user_agent(user_agent)
	{
	}

}
