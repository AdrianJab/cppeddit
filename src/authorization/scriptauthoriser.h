#include "baseauthoriser.h"
#include "credidentials.h"

#include <jsoncpp/json/json.h>
#include <cpr/cpr.h>

#include <string>

namespace Cppeddit {

	class ScriptAuthoriser : public BaseAuthoriser {
	public:
		ScriptAuthoriser(const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent);

		// Inherited via BaseAuthoriser
		virtual void authorise() override;
	private:
		virtual void request_token() override;
		virtual void refresh_token() override;
		virtual void revoke_token() override;

		cpr::Response send_request(const std::string& grant_type);
		cpr::Response send_revoke_request();

		Json::Reader m_reader;

		std::string m_last_token_type;
	};

}