#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main(
    int argc,
    char** argv
)
{
    return Catch::Session().run(argc, argv);
}
