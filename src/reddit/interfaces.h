#include <jsoncpp/json/json.h>

#include <string>
#include <vector>
#include <optional>

namespace Cppeddit {
	namespace Interfaces {
		using namespace std;
		struct Thing {
			string id;
			string name;
			string kind;
			Json::Value data;
		};

		struct Listing {
			string before;
			string after;
			string modhash;
			vector<Thing> children;
		};

		struct Votable : public Thing {
			int ups;
			int downs;
			optional<bool> likes;
		};

		struct Created : public Thing {
			long long created;
			long long created_utc;
		};
	}
}