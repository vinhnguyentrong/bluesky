cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(bluesky VERSION 0.1.0)

include(ExternalProject)

set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_DIR})

# # build foonathan-memory
# ExternalProject_Add(memory_lib
#    SOURCE_DIR
#       ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/memory
#    CMAKE_ARGS
#       -DCMAKE_CXX_COMPILER=${CMAKE_COMPILER}
#       -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
#       -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
#       -DFOONATHAN_MEMORY_BUILD_TESTS=OFF
#    BUILD_COMMAND
#       cmake --build . --target install
# )
# add_library(memory STATIC IMPORTED GLOBAL)
# set_property(
#    TARGET memory 
#    PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/libfoonathan_memory-0.7.0${MEMORY_DEBUG}.a)
# add_dependencies(memory memory_lib)

# # build fastcdr
# ExternalProject_Add(fastcdr_lib
#    SOURCE_DIR
#       ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/Fast-CDR
#    CMAKE_ARGS
#       -DCMAKE_CXX_COMPILER=${CMAKE_COMPILER}
#       -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
#       -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
#    BUILD_COMMAND
#       cmake --build . --target install
# )
# add_library(fastcdr STATIC IMPORTED GLOBAL)
# set_property(TARGET fastcdr PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/libfastcdr.so)
# add_dependencies(fastcdr fastcdr_lib)

# # build tinyxml2
# ExternalProject_Add(tinyxml2_lib
#    SOURCE_DIR
#       ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/tinyxml2
#    CMAKE_ARGS
#       -DCMAKE_CXX_COMPILER=${CMAKE_COMPILER}
#       -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
#       -Dtinyxml2_SHARED_LIBS=ON
#       -Dtinyxml2_BUILD_TESTING=OFF
#       -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
#    BUILD_COMMAND
#       cmake --build . --target install
# )
# add_library(tinyxml2 STATIC IMPORTED GLOBAL)
# set_property(TARGET tinyxml2 PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/libtinyxml2.a)
# add_dependencies(tinyxml2 tinyxml2_lib)

# build googletest
if(BUILD_TESTS)
   ExternalProject_Add(googletest_lib
      SOURCE_DIR
         ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/googletest
      CMAKE_ARGS
         -DCMAKE_CXX_COMPILER=${CMAKE_COMPILER}
         -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
         -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
      BUILD_COMMAND
         cmake --build . --target install
   )
   add_library(libgoogletest STATIC IMPORTED)
   set_property(TARGET libgoogletest PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/libgtest.a)
   set_property(TARGET libgoogletest PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/libgtest_main.a)
   set_property(TARGET libgoogletest PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/libgmock.a)
   set_property(TARGET libgoogletest PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/libgmock_main.a)
   # set_public_header(TARGET googletest PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/include)
   # set_target_properties()
   add_dependencies(libgoogletest googletest_lib)

endif(BUILD_TESTS)

# # message(${BUILD_TESTS})
# ExternalProject_Add(fastrtps_lib
#    SOURCE_DIR
#       ${CMAKE_CURRENT_SOURCE_DIR}/../fastdds
#    CMAKE_ARGS
#       -DCMAKE_CXX_COMPILER=${CMAKE_COMPILER}
#       -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
#       -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
#       -DBUILD_SHARED_LIBS=ON
#       -DAsio_INCLUDE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/asio/asio/include
#       -DCOMPILE_EXAMPLES=${BUILD_EXAMPLES}
#       -DPERFORMANCE_TESTS=${BUILD_TESTS}
#       -DPROFILING_TESTS=${BUILD_TESTS}
#       -DEPROSIMA_BUILD_TESTS=${BUILD_TESTS}
#    BUILD_COMMAND
#       cmake --build . --target install -- -j4
#    DEPENDS
#       fastcdr
#       memory
#       tinyxml2
#       # googletest
# )
# add_library(fastrtps STATIC IMPORTED GLOBAL)
# # set_property(TARGET fastrtps IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib)

add_subdirectory(modernCpp)
