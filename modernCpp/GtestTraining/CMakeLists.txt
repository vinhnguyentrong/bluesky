# find_package(GTest)
# find_package(GMock)


set(
    UTEST_DB_SOURCE
    src/Database.cpp
    utest/UTestDatabase.cpp
)

set(
    UTEST_FIXTURE
    utest/UTestFixture.cpp
)
# message(${CMAKE_INSTALL_PREFIX})



add_executable(UtestDatabase ${UTEST_DB_SOURCE})
add_executable(UtestFixture ${UTEST_FIXTURE})
# include_directories(${CMAKE_INSTALL_PREFIX}/include)
# add_dependencies(UtestDatabase googletest)

target_link_libraries(UtestDatabase
    ${CMAKE_INSTALL_PREFIX}/lib/libgtest.a
    ${CMAKE_INSTALL_PREFIX}/lib/libgtest_main.a
    ${CMAKE_INSTALL_PREFIX}/lib/libgmock_main.a
    ${CMAKE_INSTALL_PREFIX}/lib/libgmock.a
    pthread
)

target_link_libraries(UtestFixture
    ${CMAKE_INSTALL_PREFIX}/lib/libgtest.a
    ${CMAKE_INSTALL_PREFIX}/lib/libgtest_main.a
    ${CMAKE_INSTALL_PREFIX}/lib/libgmock_main.a
    ${CMAKE_INSTALL_PREFIX}/lib/libgmock.a
    pthread
)
# target_link_libraries(UtestDatabase libgoogletest)
# target_link_libraries(UtestDatabase pthread)
target_include_directories(UtestDatabase PUBLIC ${CMAKE_INSTALL_PREFIX}/include)
target_include_directories(UtestDatabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(UtestDatabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utest)

target_include_directories(UtestFixture PUBLIC ${CMAKE_INSTALL_PREFIX}/include)


# set_property(TARGET UtestDatabase IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib)
