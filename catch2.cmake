FetchContent_Declare(
    catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
    GIT_TAG         v2.13.1
    GIT_SHALLOW     true
)

FetchContent_MakeAvailable(catch2)

set(CATCH_BUILD_TESTING OFF CACHE_INTERNAL "")
set(CATCH_BUILD_TESTING OFF CACHE_INTERNAL "")
set(CATCH_INSTALL_DOCS OFF CACHE_INTERNAL "")
set(BUILD_TESTING OFF CACHE_INTERNAL "")

include_directories(
    "${catch2_SOURCE_DIR}/single_include")
