#pragma once

#include "interfaces.h"

#include <jsoncpp/json/json.h>

#include <memory>

namespace Cppeddit {
	namespace Deserialisation {
		std::unique_ptr<Interfaces::Listing> make_listing(const std::string& json);

		//TODO Refactor - use unique_ptr
		//Interfaces::Thing make_thing(const std::string& json);
	};
}