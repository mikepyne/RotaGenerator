
#include <QApplication>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "mainwindow.h"

/// \mainpage %Rota Generator
///
/// \section Introduction
///
/// Generate rotas for events.

void initialise_logging(
//    const std::string& name
)
{
    auto console{std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
    console->set_level(spdlog::level::trace);
    console->set_pattern("%T [%^%l%$] %v");

    auto file{std::make_shared<spdlog::sinks::daily_file_sink_mt>("rota_generator",
                                                                  0, 0, false, 5)};

    file->set_level(spdlog::level::debug);
    file->set_pattern("%T %l %v");

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(console);
    sinks.push_back(file);

    auto rg_logger{std::make_shared<spdlog::logger>("rota_generator",
                                                    begin(sinks), end(sinks))};

    rg_logger->set_level(spdlog::level::trace);
    spdlog::register_logger(rg_logger);
    spdlog::set_default_logger(rg_logger);
}

int main(int argc, char *argv[])
{
    initialise_logging();
    spdlog::debug("Starting Rota Generator");
    QApplication a(argc, argv);
    a.setApplicationName("RotaGenerator");
    MainWindow w;
    w.show();
    spdlog::debug("Done");
    return a.exec();
}
