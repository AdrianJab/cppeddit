#include "interfaces.h"

#include <iostream>

namespace Cppeddit {
	namespace Interfaces {
		Thing Thing::create(const std::string& kind, const Json::Value& data)
		{
			return Thing{};
		}
		Listing Listing::create(const Json::Value& data)
		{
			for (auto itr : data["children"]) {
				std::cout << "Listing has child thing object of kind " << itr["kind"].asString()
					<< " and data: " << itr["data"] << std::endl;
			}
			return Listing{data["before"].asString(), data["after"].asString(), data["modhash"].asString() };
		}
	}
}
