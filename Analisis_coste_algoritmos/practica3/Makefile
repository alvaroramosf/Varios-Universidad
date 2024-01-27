#------------------------------------------------------------------------------
# File:   Makefile
# Author: Álvaro Ramos Fustero
# Date:   febrero 2022
#------------------------------------------------------------------------------

#---------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -std=c++11      #opciones de compilación
LDFLAGS =                      #opciones de linkado
RM = rm -f                     #comando para borrar ficheros

all: calmsolape
#-----------------------------------------------------------
# Compilacion
calmsolape.o: calmsolape.cpp
	${CC} -c calmsolape.cpp -I ${CPPFLAGS}
# Linkado
calmsolape: calmsolape.o maxsolape.o
	${CC} calmsolape.o maxsolape.o -o calmsolape ${LDFLAGS}
maxsolape.o: maxsolape.cpp maxsolape.hpp
	${CC} -c maxsolape.cpp -I  ${CPPFLAGS}
#-----------------------------------------------------------	
clean:
	${RM} maxsolape.o calmsolape.o calmsolape
