#ifndef LOGGER_FACTORY_HPP
#define LOGGER_FACTORY_HPP

#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class LoggerFactory {
public:
    /**
     * @brief Método estático para obter o logger
     * @param name Nome do Logger
     * @return Instância de Logger
     */
    static std::shared_ptr<spdlog::logger> get_logger(const std::string& name = "");
};

#endif
