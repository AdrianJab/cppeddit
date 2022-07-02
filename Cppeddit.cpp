// Cppeddit.cpp : Defines the entry point for the application.
//

#include "Cppeddit.h"

#include <cpr/cpr.h>

using namespace std;

int main(int argc, char** argv) {
    /*cpr::Response r = cpr::Get(cpr::Url{ "https://api.github.com/repos/whoshuu/cpr/contributors" },
        cpr::Authentication{ "user", "pass" },
        cpr::Parameters{ {"anon", "true"}, {"key", "value"} });
    std::cout << "Status code: " << r.status_code << '\n';
    std::cout << "Header:\n";
    for (const std::pair<std::string, std::string>& kv : r.header) {
        std::cout << '\t' << kv.first << ':' << kv.second << '\n';
    }
    std::cout << "Text: " << r.text << '\n';*/

    std::string TOKEN_BASE_URL = "https://www.reddit.com/api/v1/access_token";
    std::string API_BASE_URL = "https://oauth.reddit.com";

    auto auth = cpr::Authentication{"WNcNIhXWakAbEaBotoBc-w","C6sVAZzv7sOOsh3UH8TUaMY9d_e4Ng"};
    auto payload = cpr::Payload{
        {"grant_type", "password"},
        {"username", "MayoJam"},
        {"password", "Edit%99ZE"}
    };
    auto headers = cpr::Header{ {"User-Agent", "windows:redditbot:0.0.1 (by u/MayoJam>)"} };
    cpr::Response r = cpr::Post(
        cpr::Url{ TOKEN_BASE_URL},
        auth,
        payload,
        headers);

    std::cout << "Status code: " << r.status_code << '\n';
    /*std::cout << "Header:\n";
    for (const std::pair<std::string, std::string>& kv : r.header) {
        std::cout << '\t' << kv.first << ':' << kv.second << '\n';
    }*/
    std::cout << "Text: " << r.text << '\n';
}
