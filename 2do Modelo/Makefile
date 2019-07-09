CC  = gcc
INC =
OPC = -g -c
LIB = -lrt
obj = $(patsubst %.c,%.o,$(wildcard *.c))

.c.o:
	$(CC) $(OPC) $(INC) $<

all:	$(obj) Servidor.out cliente.out

Servidor.out: Servidor.o
	$(CC) -o $@ $^

cliente.out: cliente.o
	$(CC) -o $@ $^


clean:
	rm -fr *.o *.out
