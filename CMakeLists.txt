CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(Quartet)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -Wall -funroll-loops")

SET(SRC_FILES src/predicates.cpp
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

ADD_LIBRARY(quartet ${SRC_FILES})
if(UNIX)
    TARGET_COMPILE_OPTIONS(quartet PRIVATE -fPIC)
    TARGET_LINK_LIBRARIES(quartet PRIVATE m)
endif(UNIX)

# build option
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O1 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -DDELEASE")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -Og -DNDEBUG")
message("Build type: " ${CMAKE_BUILD_TYPE})

# build path
message("Current directory: " ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

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
set(CMAKE_OSX_ARCHITECTURES x86_64)

add_executable(sample openvdb/main.cpp)
target_link_libraries(
        sample
        ${TBB_LIBRARY}
        ${OpenVDB_LIBRARY}
)

ADD_EXECUTABLE(quartet_bin cli/main.cpp)
TARGET_LINK_LIBRARIES(quartet_bin PRIVATE
        quartet
        ${OpenVDB_LIBRARY}
        openvdb
        ${Boost_LIBRARIES}
        )
SET_TARGET_PROPERTIES(quartet_bin PROPERTIES OUTPUT_NAME quartet)

INSTALL(TARGETS quartet quartet_bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    )
INSTALL(FILES
    src/array3.h
    src/feature.h
    src/geometry_queries.h
    src/gluvi.h
    src/make_signed_distance.h
    src/make_tet_mesh.h
    src/match_features.h
    src/optimize_tet_mesh.h
    src/read_obj.h
    src/sdf.h
    src/tet_mesh.h
    src/tet_quality.h
    src/trimesh.h
    src/util.h
    src/vec.h
    DESTINATION include/quartet)
