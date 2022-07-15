#include "deserialiser.h"

namespace Cppeddit {
	namespace Deserialisation {
		Interfaces::Thing make_thing(const std::string& json)
		{
			Json::Reader reader;
			Json::Value root;
			reader.parse(json, root);

			auto t = Interfaces::Thing::create(root["kind"].asString(), root);

			return t;
		}
		Interfaces::Listing make_listing(const std::string& json)
		{
			Json::Reader reader;
			Json::Value root;
			reader.parse(json, root);

			auto l = Interfaces::Listing::create(root["data"]);

			return l;
		}
	}
}