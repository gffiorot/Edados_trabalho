# Flags do compilador
CFLAGS = -Wall -g

# Sources 
SRCS = main.c bd_paciente.c arquivo.c interface_usuario.c

# Objetos
OBJ = $(SRCS:.c=.o)

# Dependências comuns (arquivos de header)
DEPS = arquivo.h bd_paciente.h interface_usuario.h

# Alvo padrão
all: sistema

# Ligação final dos objetos para gerar o executável
sistema: $(OBJ)
	$(CC) $(CFLAGS) -o sistema $(OBJ)

# Regra genérica para compilar arquivos .c em .o
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Limpar arquivos objeto e o executável
clean:
	del /Q *.o sistema.exe

# Executa o programa (target opcional)
run: sistema
	./sistema