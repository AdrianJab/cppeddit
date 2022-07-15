#pragma once

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

			static Thing create(const std::string& kind, const Json::Value& data);
		};

		struct Listing {
			std::string before;
			std::string after;
			std::string modhash;
			std::vector<Thing> children;

			//Since we know the type is Listing we don't have to read kind
			static Listing create(const Json::Value& data);
		};

		struct Votable : virtual Thing {
			int ups;
			int downs;
			std::optional<bool> likes;
		};

		struct Created : virtual Thing {
			long long created;
			long long created_utc;
		};

		struct Link : Votable, Created {
			//TODO Link aka post data
		};
	}
}