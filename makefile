# Nome do executável
EXEC_NAME = programa

# Nome do zip
ZIP_NAME = programa.zip

# Lista de arquivos fonte
SOURCES = main.cpp classes/logger_factory.cpp

# Gerar lista de headers automaticamente (qualquer .cpp que não seja main.cpp)
HEADERS = $(patsubst %.cpp,%.hpp,$(filter-out main.cpp,$(SOURCES)))

# Lista todos os arquivos envolvidos
FILES = $(SOURCES) $(HEADERS) makefile

# Definir o compilador
CXX = g++

# Definir flags do compilador
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Flags de ligação (linking) para bibliotecas
LDFLAGS = -lspdlog -lfmt

# Gerar a lista de arquivos objeto a partir dos arquivos fonte
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão para compilar o projeto
all: $(EXEC_NAME)

# Regra para gerar o executável
$(EXEC_NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regra para compilar arquivos .cpp em .o e gerar dependências
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Incluir dependências geradas automaticamente
-include $(SOURCES:.cpp=.d)

# run: Compila e roda o programa
run: $(EXEC_NAME)
	./$(EXEC_NAME)

# zip: Zippa os arquivos fonte
zip: $(ZIP_NAME)

$(ZIP_NAME): $(FILES)
	zip -r $(ZIP_NAME) $(FILES)

# clean: Limpa todos os arquivos gerados da compilação
clean:
	rm -f $(OBJECTS)
	rm -f $(SOURCES:.cpp=.d)
	rm -f $(EXEC_NAME)

# valgrind: Regra para executar o programa com o Valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_NAME)

finish: all run clean zip

.PHONY: all clean run zip
