#pragma once

#include "interfaces.h"

#include <jsoncpp/json/json.h>

namespace Cppeddit {
	namespace Deserialisation {
		Interfaces::Listing make_listing(const std::string& json);

		//TODO Refactor - use unique_ptr
		//Interfaces::Thing make_thing(const std::string& json);
	};
}