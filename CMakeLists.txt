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
TARGET_LINK_LIBRARIES(quartet PRIVATE m)

ADD_EXECUTABLE(quartet_bin src/main.cpp)
TARGET_LINK_LIBRARIES(quartet_bin PRIVATE quartet)
