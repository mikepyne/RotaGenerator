#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <gtest/gtest.h>

void initialise_logging()
{
    auto console {std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
    console->set_level(spdlog::level::trace);
    console->set_pattern("%T [%^%l%$] %v");

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(console);

    auto test_logger {std::make_shared<spdlog::logger>("test_logger",
                                                   begin(sinks), end(sinks))};

    test_logger->set_level(spdlog::level::trace);
    spdlog::register_logger(test_logger);
    spdlog::set_default_logger(test_logger);
}

int main(
    int argc,
    char** argv
)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
