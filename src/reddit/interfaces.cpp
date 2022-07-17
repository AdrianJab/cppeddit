#include "interfaces.h"

#include <iostream>

namespace Cppeddit {
	namespace Interfaces {
		Listing Listing::create(const Json::Value& data)
		{
			std::vector<Post> posts;
			for (auto child : data["children"]) {
				std::cout << "Listing has child thing object of kind " << child["kind"].asString()
					<< " and data: " << child["data"] << std::endl;

				//Todo Check kind of child object and then instantiate correct object into list

				posts.push_back(Post::create(child["data"]));
				break;
			}
			return Listing{ data["before"].asString(), data["after"].asString(), data["modhash"].asString(), posts };
		}

		Post Post::create(const Json::Value& data)
		{
			return { data };
		}

		Thing::Thing(const const Json::Value& input_data) :
			id{ input_data["id"].asString() },
			name{ input_data["name"].asString() },
			data{ input_data["data"] }
		{
			auto end = name.find("_");
			if (end != std::string::npos)
				kind = name.substr(0, end);
			//TODO Are there kinds not starting with "t[1-6]_" ?
		}

		Votable::Votable(const const Json::Value& input_data) :
			Thing{ input_data },
			ups{ input_data["ups"].asInt() },
			downs{ input_data["downs"].asInt() }
		{
			if (input_data["likes"].isBool()) {
				likes = input_data["likes"].asBool();
			}
			else {
				likes = std::nullopt;
			}
		}

		Created::Created(const const Json::Value& input_data) :
			Thing{ input_data },
			created{ input_data["created"].asLargestInt() },
			created_utc{ input_data["created_utc"].asLargestInt() }
		{
		}
		Post::Post(const const Json::Value& input_data) :
			Thing{input_data},
			Votable{input_data},
			Created{input_data}
		{
		}
	}
}
