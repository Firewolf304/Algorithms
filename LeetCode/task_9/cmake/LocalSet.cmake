set(CMAKE_TEST_PROJECTNAME "test_${PROJECT_NAME}")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "" FORCE)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE) # if cant build with "ld.lld: error: undefined symbol: main" set it to FALSE