enable_testing()

if(BUILD_TESTING)

    if(NOT TARGET GTest::GTest)
        find_package(GTest CONFIG REQUIRED)
    endif()
    message(STATUS "Add GTest for custom target")
    add_executable(${CMAKE_TEST_PROJECTNAME} test.cpp)
    target_link_libraries(${CMAKE_TEST_PROJECTNAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

    if(TARGET GTest::gtest)
        message(STATUS "Using GTest from root configuration")
    else()
        message(FATAL_ERROR "GTest not found but BUILD_TESTS is ON")
    endif()

    include(GoogleTest)
    gtest_discover_tests(${CMAKE_TEST_PROJECTNAME}
        DISCOVERY_MODE PRE_TEST
        EXTRA_ARGS --gtest_color=yes
        # OPTIONAL: указать рабочую директорию/паттерны:
        # WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )

    message(STATUS "Add target ${CMAKE_TEST_PROJECTNAME}")
    add_custom_target(
        run_all_tests
        DEPENDS ${CMAKE_TEST_PROJECTNAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND}
        COMMENT "Running all tests"
        VERBATIM
    )
endif()

