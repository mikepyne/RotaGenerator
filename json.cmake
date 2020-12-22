FetchContent_Declare(
    json
    GIT_REPOSITORY  https://github.com/nlohmann/json.git
    GIT_TAG         v3.9.1
)

FetchContent_MakeAvailable(json)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")

include_directories(
    "${json_SOURCE_DIR}/include"
)
