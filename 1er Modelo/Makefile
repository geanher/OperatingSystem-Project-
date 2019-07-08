CC  = gcc
INC =
OPC = -g -c
LIB = -lrt
obj = $(patsubst %.c,%.o,$(wildcard *.c))

.c.o:
	$(CC) $(OPC) $(INC) $<

all:	$(obj) CamaraSeguridad.out Automovil.out

CamaraSeguridad.out: CamaraSeguridad.o
	$(CC) -o $@ $^

Automovil.out: Automovil.o
	$(CC) -o $@ $^


clean:
	rm -fr *.o *.out
