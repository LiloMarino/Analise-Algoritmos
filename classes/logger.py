import logging


class LoggerFactory:
    @staticmethod
    def get_logger(name: str | None = None):
        logger = logging.getLogger(name)
        logger.setLevel(logging.INFO)

        # Formato do log para incluir o nome da função
        if name is not None:
            formatter = logging.Formatter("[%(name)s] %(message)s")
        else:
            formatter = logging.Formatter("[%(funcName)s] %(message)s")

        # Handler para o arquivo
        file_handler = logging.FileHandler("info.log", mode="w", encoding="utf-8")
        file_handler.setFormatter(formatter)

        # Handler para o terminal
        stream_handler = logging.StreamHandler()
        stream_handler.setFormatter(formatter)

        # Adiciona os handlers ao logger
        if not logger.handlers:
            logger.addHandler(file_handler)
            logger.addHandler(stream_handler)

        return logger
