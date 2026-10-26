# Cpp Template Project (VSCode + CMake + Ninja)

This is a starter template for C++ projects using:
* CMake (with presets for GCC/Clang)
* Ninja as the build system
* vcpkg for dependency management
* VSCode for development and debugging

## Project structure
```
.
├── CMakeLists.txt              # Main CMake entry point
├── CMakePresets.json           # Build presets
├── LICENSE
├── README.md
├── cmake/                      # Custom CMake helper scripts
│   ├── LinkerSettings.cmake    # Linker auto detector
│   ├── Packages.cmake          # Package list
│   ├── Targets.cmake           # Target list
│   ├── Vcpkg.cmake             # Vcpkg detector
│   └── VcpkgInstall.cmake      # Vcpkg installer
├── config.json                 # Project configuration
├── docker/
│   └── Dockerfile              # Build environment
├── docs/
│   └── installs.md             # Setup and dependencies notes
├── include/
│   ├── dotenv-cpp.hpp          # Dotenv lib
│   └── lib.hpp                 # Lib example
├── src/
│   ├── lib.cpp                 # Source example
│   └── main.cpp                # Main file
└── vcpkg.json                  # vcpkg manifest with dependencies
```

## Building
his project uses CMakePresets (requires CMake ≥ 3.30.8).
Available configure presets:

* ninja-gcc-debug — Debug build with GCC
* ninja-clang-debug — Debug build with Clang

Build workflow:
```
# Configure with GCC
cmake --preset ninja-gcc-debug

# Build
cmake --build --preset gcc-debug -j
```
Build artifacts are placed in ./ninja-gcc-debug/ or ./ninja-clang-debug/.

## Docs
* [Install](docs/installs.md)

## TODO
- [ ] Add docker deploy/debug
- [ ] Add tests
- [ ] Add CI/CD tests
- [ ] Add vcpkg autodeploy
- [ ] Add old ```make``` support
- [x] Add clang-format
- [ ] Add clang-tidy
- [x] Add Release (gcc/clang)
- [x] Add BuildConfig
- [x] Add tests
- [x] Refactor locallib link to ```only headers``` and add local ```target link sources```
- [ ] Add fuze testing
- [ ]


