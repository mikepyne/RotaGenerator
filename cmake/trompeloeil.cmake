FetchContent_Declare(
    trompeloeil
    GIT_REPOSITORY  https://github.com/rollbear/trompeloeil.git
    GIT_TAG         v39
    GIT_SHALLOW     true
)

set(TROMPELOEIL_INSTALL_DOCS OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(trompeloeil)
