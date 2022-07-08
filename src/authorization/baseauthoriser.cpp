#include "baseauthoriser.h"
#include "token.h"

#include <iostream>

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

	void BaseAuthoriser::load_token(Json::Value&& token_data)
	{
		try
		{
			m_current_token = Token::from_json(std::move(token_data));
		}
		catch (const bad_token_data& e)
		{
			std::cerr << "Token load failed. Reason: " << e.what();
		}
	}

}
