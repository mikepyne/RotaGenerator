FetchContent_Declare(
    json
    GIT_REPOSITORY  https://github.com/nlohmann/json.git
    GIT_TAG         v3.9.1
)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_CI OFF CACHE INTERNAL "")
set(JSON_Diagnostics OFF CACHE INTERNAL "")
set(JSON_ImplicitConversions ON CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
set(JSON_MultipleHeaders OFF CACHE INTERNAL "")
set(JSON_SystemInclude OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(json)

include_directories(
    "${json_SOURCE_DIR}/include"
)
