# fichero Makefile
#
# nombre del fichero ejecutable
#
# VARIABLES
BIN 	= bin
SRC 	= src
OBJ 	= obj
LIB 	= lib
INCLUDE = include

TARGETS= practica4

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) -Wno-deprecated
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) -Wno-deprecated

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut -ljpeg

# definicion del compilador
#
CC =  g++ -Ofast -Wno-write-strings

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#
practica4: objetos.o practica4.o grua.o file_ply_stl.o jpg_imagen.o jpg_memsrc.o jpg_readwrite.o
	  $(CXX) -o practica4 objetos.o practica4.o grua.o file_ply_stl.o jpg_imagen.o jpg_memsrc.o jpg_readwrite.o  $(LDFLAGS)

grua.o :  grua.cpp
	$(CC) -o $@ -c $(CXXFLAGS) grua.cpp  $(LDFLAGS)

objetos.o :  objetos.cpp jpg_imagen.hpp 
	$(CC) -o $@ -c $(CXXFLAGS) objetos.cpp  $(LDFLAGS)

practica4.o :  practica4.cc
	$(CC) -o $@ -c $(CXXFLAGS) practica4.cc  $(LDFLAGS)

file_ply_stl.o :  file_ply_stl.cc
		$(CC) -o $@ -c $(CXXFLAGS) file_ply_stl.cc  $(LDFLAGS)

jpg_imagen.o :  jpg_imagen.cpp 
		$(CC) -o $@ -c $(CXXFLAGS) jpg_imagen.cpp  $(LDFLAGS)

jpg_readwrite.o :  jpg_readwrite.cpp jpg_memsrc.hpp
		$(CC) -o $@ -c $(CXXFLAGS) jpg_readwrite.cpp  $(LDFLAGS)
		
jpg_memsrc.o :  jpg_memsrc.cpp
		$(CC) -o $@ -c $(CXXFLAGS) jpg_memsrc.cpp  $(LDFLAGS)



#
#
#g++ -o
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *
