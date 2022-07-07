// Cppeddit.cpp : Defines the entry point for the application.

#include "Cppeddit.h"

#include "client/client.h"

#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    std::ifstream infile("secrets");
    std::string line;

    std::string client_id;
    std::string client_secret;
    std::string username;
    std::string password;
    std::string user_agent;
    std::getline(infile, client_id);
    std::getline(infile, client_secret);
    std::getline(infile, username);
    std::getline(infile, password);
    std::getline(infile, user_agent);

    Cppeddit::Client client {
        Cppeddit::AppType::Script,
        client_id,
        client_secret,
        username,
        password,
        user_agent
    };
}
