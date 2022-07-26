#include "baseauthoriser.h"
#include "credidentials.h"
#include "client/rest/restclient.h"

#include <jsoncpp/json/json.h>
#include <cpr/cpr.h>

#include <string>

namespace Cppeddit {

	class ScriptAuthoriser : public BaseAuthoriser {
	public:
		ScriptAuthoriser(const Credidentials& client_data, const Credidentials& user_data, const std::string& user_agent);

		// Inherited via BaseAuthoriser
		virtual std::string authorise() override;
	private:
		virtual void request_token() override;
		virtual void refresh_token() override;
		virtual void revoke_token() override;

		void generate_token(const std::string& payload);

		Rest::RequestData make_request(const cpr::Payload& payload) const;

		Json::Reader m_reader;

		std::string m_last_token_type;

		Rest::Client m_client;
	};

}