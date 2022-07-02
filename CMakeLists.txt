# CMakeList.txt : CMake project for Cppeddit, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Cppeddit")

# Add source to this project's executable.
add_executable (Cppeddit "Cppeddit.cpp" "Cppeddit.h")

# TODO: Add tests and install targets if needed.

set(CMAKE_CXX_STANDARD 11)

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG db351ffbbadc6c4e9239daaa26e9aefa9f0ec82d) # The commit hash for 1.8.2. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(Cppeddit PRIVATE cpr::cpr)

# target_link_libraries(Cppeddit ${CPR_LIB})
# target_include_directories(Cppeddit PRIVATE include)
