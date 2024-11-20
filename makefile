# Nome do executável
TARGET = programa

# Arquivos fonte
SRCS = main.c expressao.c

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Regra padrão
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
