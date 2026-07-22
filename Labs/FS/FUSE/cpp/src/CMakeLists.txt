add_library(locallib STATIC)

target_sources(locallib PUBLIC
  FILE_SET CXX_MODULES
  BASE_DIRS ../include
  FILES
    ../include/types/base.ixx
    ../include/types/vfile.ixx
    ../include/types.ixx
    ../include/lib.ixx
)

target_include_directories(locallib PUBLIC ../include)