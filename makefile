
CC= gcc -c

CLINKER= gcc -lm -lpthread -o

FLAGS= -O3 -Wall  

OBJ= main.o \
	carga_localidades.o \
	carga_recursos.o \
	carga_segmento.o \
	carga_nodos.o \
	aasocia_loc2nodo.o \
	aasocia_rec2nodo.o \
	agenera_red.o \
	aprincipal.o \
	salida.o


DIR_SRC=./src/

DIR_BIN=./bin/


all: sclean $(OBJ)
	$(CLINKER) $(DIR_BIN)distlocrutac.exe $(OBJ) $(FLAGS)
	@rm -rf *.o


%.o: $(DIR_SRC)%.c
	$(CC) $(FLAGS) $<


clean:
	@rm -rfv *.o


sclean:
	@rm -rfv *.o
	@rm -rfv $(DIR_BIN)*.exe