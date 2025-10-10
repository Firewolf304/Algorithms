target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# local includes
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE locallib)