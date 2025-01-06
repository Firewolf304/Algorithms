# CMakeList.txt: проект CMake для Coroutine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Coroutine "Coroutine.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Coroutine PROPERTY CXX_STANDARD 23)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
