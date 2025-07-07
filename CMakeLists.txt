set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# -----------------------------------------------------------------------------
# Specifying the minimum CMake version required.
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0148 NEW)


# Locate the Python interpreter, headers, and libraries (all in one)
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Tell pybind11 to use the new FindPython mechanism
set(PYBIND11_FINDPYTHON ON)

# Now bring in pybind11
find_package(pybind11 CONFIG REQUIRED)

# -----------------------------------------------------------------------------
# Declare the project name and the languages it will use.
# - PROJECT_NAME will be set to "volsurf"
# - We explicitly state we’re using C++ (CXX)
# -----------------------------------------------------------------------------
project(volsurf LANGUAGES CXX)

# -----------------------------------------------------------------------------
# Enforce using C++17 standard:
# - CMAKE_CXX_STANDARD: which standard to use
# - CMAKE_CXX_EXTENSIONS: OFF means “no compiler-specific extensions”
# - CMAKE_CXX_STANDARD_REQUIRED: ON means fail if the compiler cannot do C++17
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)             # request ISO C++17
set(CMAKE_CXX_EXTENSIONS OFF)          # disable GNU/MSVC extensions
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # error out if C++17 isn’t supported

# -----------------------------------------------------------------------------
# Find and link OpenMP support if the compiler provides it.
# Commenting for now to avoid errors
# -----------------------------------------------------------------------------
# find_package(OpenMP)                   # search for OpenMP
# if(OpenMP_CXX_FOUND)                   # only true if a C++ OpenMP toolset is found
#   # Link the imported OpenMP target into our library’s PUBLIC interface.
#   # PUBLIC means downstream targets will also compile with OpenMP flags.
#   target_link_libraries(
#     ${PROJECT_NAME}                    # our main library target
#     PUBLIC
#       OpenMP::OpenMP_CXX               # the standard imported OpenMP C++ target
#   )
# endif()

# -----------------------------------------------------------------------------
# Locate the Eigen3 header-only library and add its include directory.
# -----------------------------------------------------------------------------
find_package(Eigen3 REQUIRED)          # error out if Eigen3 isn’t found
# include_directories is a global include; can also use target_include_directories
include_directories(
  ${EIGEN3_INCLUDE_DIR}                # path to Eigen’s headers
)

# -----------------------------------------------------------------------------
# Gather all of our source (*.cpp) and header (*.hpp) files recursively.
# - GLOB_RECURSE: finds files in subdirectories matching pattern
# - Useful for small projects; remember CMake must be re-run if you add files.
# -----------------------------------------------------------------------------
file(GLOB_RECURSE
  CPP_SOURCES                          # variable to hold all .cpp files
    src/*.cpp
)
file(GLOB_RECURSE
  HEADER_FILES                         # variable to hold all .hpp files
    include/*.hpp
)

# -----------------------------------------------------------------------------
# Create a library target from our collected sources and headers.
# - add_library: declares a library target named ${PROJECT_NAME}
# -----------------------------------------------------------------------------
add_library(
  ${PROJECT_NAME}                      # the target name: "volsurf"
  ${CPP_SOURCES}                       # all .cpp implementation files
  ${HEADER_FILES}                      # all .hpp declarations (for IDEs, installs)
)

# -----------------------------------------------------------------------------
# Ensure users of our library can include headers from our include/ directory.
# - PUBLIC: both this target and anything that links to it will get this include path.
# -----------------------------------------------------------------------------
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # top-level include folder
)

# -----------------------------------------------------------------------------
# Build the Python bindings module:
# - Name the resulting module "volsurf_bindings"
# - Source lives in bindings/bindings.cpp
# -----------------------------------------------------------------------------
pybind11_add_module(
  volsurf_bindings                    # module name in Python
  bindings/bindings.cpp               # C++ source for the binding
)

# Link the bindings module against our core C++ library:
target_link_libraries(
  volsurf_bindings
  PRIVATE
    ${PROJECT_NAME}                   # only the bindings need to see our lib
)

# -----------------------------------------------------------------------------
# Create a standalone test executable:
# - Named test_iv, source in tests/test_iv.cpp
# -----------------------------------------------------------------------------
add_executable(
  test_iv                             # test executable name
  tests/test_iv.cpp                   # test source file
)

# Link the test program against our library so it can call its functions:
target_link_libraries(
  test_iv
  PRIVATE
    ${PROJECT_NAME}
)