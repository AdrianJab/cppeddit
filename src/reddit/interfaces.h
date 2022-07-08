#include <jsoncpp/json/json.h>

#include <string>
#include <vector>
#include <optional>

namespace Cppeddit {
	namespace Interfaces {
		struct Thing {
			std::string id;
			std::string name;
			std::string kind;
			Json::Value data;
		};

		struct Listing {
			std::string before;
			std::string after;
			std::string modhash;
			std::vector<Thing> children;
		};

		struct Votable : public Thing {
			int ups;
			int downs;
			std::optional<bool> likes;
		};

		struct Created : public Thing {
			long long created;
			long long created_utc;
		};
	}
}