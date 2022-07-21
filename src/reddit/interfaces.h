#pragma once

#include <jsoncpp/json/json.h>

#include <string>
#include <vector>
#include <optional>

namespace Cppeddit {
	namespace Interfaces {
		struct Post;

		struct Thing {
			std::string id;
			std::string name;
			std::string kind;
			Json::Value data;

			virtual ~Thing() = default;

		protected:
			Thing(const Json::Value& input_data);
		};

		struct Listing {
			std::string before;
			std::string after;
			std::string modhash;
			std::vector<std::unique_ptr<Thing>> children;

			//Since we know the type is Listing we don't have to read kind
			static std::unique_ptr<Listing> create(const Json::Value& data);

			Listing(const std::string& before, const std::string& after, const std::string& modhash, std::vector<std::unique_ptr<Thing>> children);
		};

		struct Votable : virtual Thing {
			int ups;
			int downs;
			std::optional<bool> likes;

			virtual ~Votable() = default;

		protected:
			Votable(const Json::Value& input_data);
		};

		struct Created : virtual Thing {
			long long created;
			long long created_utc;

			virtual ~Created() = default;

		protected:
			Created(const Json::Value& input_data);
		};

		//also called link in documentation
		//kind: t3
		struct Post final : Votable, Created {
			//TODO Link aka post data
			enum MediaType {
				Image,
				Video
			};

			static std::unique_ptr<Post> create(const Json::Value& data);

		private:
			Post(const Json::Value& input_data);
		};
	}
}