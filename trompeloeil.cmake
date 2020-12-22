FetchContent_Declare(
    trompeloeil
    GIT_REPOSITORY  https://github.com/rollbear/trompeloeil.git
    GIT_TAG         v39
    GIT_SHALLOW     true
)

FetchContent_MakeAvailable(trompeloeil)

set(TROMPELOEIL_INSTALL_DOCS OFF CACHE_INTERNAL "")

include_directories(
    "${trompeloeil_SOURCE_DIR}/include/catch2")
