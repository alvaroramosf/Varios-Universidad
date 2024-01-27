#------------------------------------------------------------------------------
# File:   Makefile
# Author: Alvaro Ramos Fustero
# Date:   junio 2022
#------------------------------------------------------------------------------

#---------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -std=c++11      #opciones de compilación
LDFLAGS =                      #opciones de linkado
RM = rm -f                     #comando para borrar ficheros

all: costemsolape
#-----------------------------------------------------------
# Compilacion
costemsolape.o: costemsolape.cpp
	${CC} -c costemsolape.cpp -I ../practica3 ${CPPFLAGS}
# Linkado
costemsolape: costemsolape.o maxsolape.o
	${CC} costemsolape.o maxsolape.o -I ../practica3 -o costemsolape ${LDFLAGS}
maxsolape.o: ../practica3/maxsolape.cpp ../practica3/maxsolape.hpp
	${CC} -c ../practica3/maxsolape.cpp -I ../practica3 ${CPPFLAGS}
#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado.
clean:
	${RM} maxsolape.o costemsolape.o costemsolape
