FetchContent_Declare(
    date_src
    GIT_REPOSITORY  https://github.com/HowardHinnant/date.git
    GIT_TAG         v3.0.0
    GIT_SHALLOW     true
)

FetchContent_MakeAvailable(date_src)
