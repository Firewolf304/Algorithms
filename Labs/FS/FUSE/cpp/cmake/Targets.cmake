target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE ${FUSE3_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${FUSE3_INCLUDE_DIRS})

# local includes
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE locallib)