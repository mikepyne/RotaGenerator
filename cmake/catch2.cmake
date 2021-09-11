FetchContent_Declare(
    catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
    GIT_TAG         v2.13.6
    GIT_SHALLOW     true
)

set(CATCH_BUILD_TESTING OFF CACHE INTERNAL "")
set(CATCH_BUILD_TESTING OFF CACHE INTERNAL "")
set(CATCH_INSTALL_DOCS OFF CACHE INTERNAL "")
set(BUILD_TESTING OFF CACHE INTERNAL "")
set(ENABLE_COVERAGE ON CACHE INTERNAL "")

FetchContent_MakeAvailable(catch2)

# Append the contrib path to the module path list, so the include command can
# find the custom Catch module.
list(APPEND
    CMAKE_MODULE_PATH
    "${catch2_SOURCE_DIR}/contrib"
    "${catch2_SOURCE_DIR}/CMake"
)

include(CTest)
include(Catch)
include(Findcodecov)
