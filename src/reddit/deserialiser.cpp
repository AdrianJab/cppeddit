#include "deserialiser.h"

namespace Cppeddit {
	namespace Deserialisation {
		//Interfaces::Thing make_thing(const std::string& json)
		//{
		//	Json::Reader reader;
		//	Json::Value root;
		//	reader.parse(json, root);

		//	auto kind = root["kind"].asString();
		//	Interfaces::Thing* thing;

		//	//TODO make better maping kind <-> string with name
		//	if (kind == "t3")
		//		thing = &Interfaces::Post::create(root);

		//	return *thing;
		//}
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