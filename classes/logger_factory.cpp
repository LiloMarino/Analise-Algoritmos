#include "logger_factory.hpp"

std::shared_ptr<spdlog::logger> LoggerFactory::get_logger(const std::string &name)
{
    std::shared_ptr<spdlog::logger> logger;

    // Cria o logger com ou sem nome, dependendo se o nome foi fornecido
    if (!name.empty())
    {
        logger = spdlog::get(name);
        if (!logger)
        {
            logger = spdlog::basic_logger_mt(name, "info.log", true);
        }
    }
    else
    {
        logger = spdlog::basic_logger_mt("default_logger", "info.log", true);
    }

    // Define o nível de log para INFO
    logger->set_level(spdlog::level::info);

    // Formato do log, incluindo o nome da função ou do logger
    if (!name.empty())
    {
        logger->set_pattern("[%n] %v");
    }
    else
    {
        logger->set_pattern("[%!] %v"); // %! é o nome da função no spdlog
    }

    // Cria um handler para o terminal
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    logger->sinks().push_back(console_sink);

    return logger;
}
