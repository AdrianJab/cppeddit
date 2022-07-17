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

		protected:
			Thing(const const Json::Value& input_data);
		};

		struct Listing {
			std::string before;
			std::string after;
			std::string modhash;
			//TODO In order to use polymorphism, we need to store unique_ptr<Thing> not Post
			std::vector<Post> children;

			//Since we know the type is Listing we don't have to read kind
			static Listing create(const Json::Value& data);
		};

		struct Votable : virtual Thing {
			int ups;
			int downs;
			std::optional<bool> likes;

		protected:
			Votable(const const Json::Value& input_data);
		};

		struct Created : virtual Thing {
			long long created;
			long long created_utc;

		protected:
			Created(const const Json::Value& input_data);
		};

		//also called link in documentation
		//kind: t3
		struct Post final : Votable, Created {
			//TODO Link aka post data
			enum MediaType {
				Image,
				Video
			};

			static Post create(const Json::Value& data);

		private:
			Post(const const Json::Value& input_data);
		};
	}
}