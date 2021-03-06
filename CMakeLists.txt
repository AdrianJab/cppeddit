﻿# CMakeList.txt : CMake project for Cppeddit, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project ("Cppeddit")

# Add source to this project's executable.
add_executable (Cppeddit "Cppeddit.cpp" "Cppeddit.h")

set_property(TARGET Cppeddit PROPERTY CXX_STANDARD 17)
set_property(TARGET Cppeddit PROPERTY CXX_STANDARD_REQUIRED ON)

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG db351ffbbadc6c4e9239daaa26e9aefa9f0ec82d) # The commit hash for 1.8.2. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

# include whole /src structure
target_include_directories(Cppeddit PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# link cpr
target_link_libraries(Cppeddit PRIVATE cpr::cpr)

# copy secrets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/secrets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


target_sources(Cppeddit PRIVATE
    "src/jsoncpp/jsoncpp.cpp"
    "src/authorization/token.cpp"
    "src/authorization/baseauthoriser.cpp"
    "src/authorization/scriptauthoriser.cpp"
    "src/authorization/credidentials.cpp"
    "src/client/client.cpp"
    "src/requests/baserequester.cpp"
    "src/requests/subreddit.cpp"
    "src/reddit/deserialiser.cpp"
    "src/reddit/interfaces.cpp"
    "src/client/rest/restclient.cpp")
