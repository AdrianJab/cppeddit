#pragma once

#include <optional>
#include <string>

namespace Cppeddit {
	namespace RequestBlock {

		struct ListingBlock {
			std::string before;
			std::string after;
			int limit;
			int count;
			std::optional<std::string> show;
		};
	}
}