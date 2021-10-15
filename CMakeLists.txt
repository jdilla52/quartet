cmake_minimum_required(VERSION 2.6)
# build option
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O1 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -DDELEASE")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -Og -DNDEBUG")
message("Build type: " ${CMAKE_BUILD_TYPE})

project(Quartet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -Wall -funroll-loops")

set(SRC_FILES src/predicates.cpp
              src/geometry_queries.cpp
              src/sdf.cpp
              src/trimesh.cpp
              src/tet_mesh.cpp
              src/feature.cpp
              src/read_obj.cpp
              src/tet_quality.cpp
              src/match_features.cpp
              src/optimize_tet_mesh.cpp
              src/make_signed_distance.cpp
              src/make_tet_mesh.cpp)
set(CMAKE_OSX_ARCHITECTURES x86_64)

include_directories(src)
add_library(quartet ${SRC_FILES})
if(UNIX)
    TARGET_COMPILE_OPTIONS(quartet PRIVATE -fPIC)
    TARGET_LINK_LIBRARIES(quartet PRIVATE m)
endif(UNIX)

# option
option(BUILD_AS_SHARED "whether to build as shared lib" OFF)

# tbb
find_library(TBB_LIBRARY tbb HINTS /usr/local/homebrew/Cellar/tbb@2020/2020_U3/lib)

# openexr
find_library(HALF_LIB half HINTS /usr/local/homebrew/lib)

# openvdb
#list(APPEND SAMPLE_INCLUDE_DIR /usr/local/homebrew/Cellar)
find_library(OpenVDB_LIBRARY openvdb HINTS /usr/local/homebrew/Cellar/openvdb/8.1.0/lib/libopenvdb.a)

include_directories(/usr/local/homebrew/include)
include_directories(/usr/local/homebrew/Cellar/tbb@2020/2020_U3/include)

add_executable(sample openvdb/main.cpp)
target_link_libraries(
        sample
        ${TBB_LIBRARY}
        ${OpenVDB_LIBRARY}
)

add_executable(quartet_bin cli/main.cpp)
target_link_libraries(quartet_bin
        quartet
        ${TBB_LIBRARY}
        ${OpenVDB_LIBRARY}
        )

# tests
if($ENV{TEST_QUARTET})
    message("Generating tests")
    add_subdirectory(test)
elseif(${TEST_QUARTET})
    message("Generating tests")
    add_subdirectory(test)
else()
    message("Building without tests")
endif()