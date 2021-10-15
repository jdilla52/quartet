#
# Create a target for executing the Catch unit tests.
#

set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC")

add_executable(quartetTest
        main.cpp
        signedDistance.cpp
        )

target_include_directories(quartetTest
        PUBLIC
        test/
        "${PROJECT_BINARY_DIR}"
        )

target_link_libraries(quartetTest
        Catch2::Catch2
        quartet
        )

cmake_policy(SET CMP0110 NEW)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)

# Load and use the .cmake file provided by Catch so all the test cases
# are made available to CTest.
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(quartetTest)