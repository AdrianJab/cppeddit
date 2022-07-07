#pragma once
#include "credidentials.h"
#include "Token.h"

#include <memory>

namespace Cppeddit {

	class BaseAuthoriser {
	public:
		virtual void authorise() = 0;
		bool active() const;

		//no copying
		BaseAuthoriser(const BaseAuthoriser&) = delete;
		BaseAuthoriser& operator=(const BaseAuthoriser&) = delete;

	protected:
		//Only child classes can use constructor
		BaseAuthoriser(const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent);

		virtual void request_token() = 0;
		virtual void refresh_token() = 0;
		virtual void revoke_token() = 0;

		std::unique_ptr<Token> m_current_token;

		const Credidentials& m_client_data;
		const Credidentials& m_user_data;
		const std::string& m_user_agent;
	};

}