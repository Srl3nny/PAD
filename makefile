
#Arquivo makefile para exercício de pthreads disciplina FT045a
#Bruno
#Data: 17/04/16
#30/05/16 teste github
CC=gcc
DIRETIVA=-lpthread
OBJ=leMatriz.o

FONTES= gera-matriz.c leMatriz.c matriz-paralelo.c matriz-serial.c
OBJETOS= $(FONTES:.c=.o)

gera-matriz.o: gera-matriz.c
	@echo "Compilando arquivo" $<
	$(CC) $< -o $@

leMatriz.o: leMatriz.c
	@echo "Compilando arquivo" $<
	$(CC) $< -c -o $@

matriz-paralelo.o: matriz-paralelo.c
	@echo "Compilando arquivo" $<
	$(CC) $< $(DIRETIVA) $(OBJ) -o $@
	
matriz-serial.o: matriz-serial.c
	@echo "Compilando arquivo" $<
	$(CC) $< $(OBJ) -o $@

all: $(OBJETOS)


clean:
	rm -f $(OBJETOS)

