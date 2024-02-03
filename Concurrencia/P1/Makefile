
CC=g++
CPPFLAGS=-I. -g -std=c++11
LDFLAGS=-pthread
RM=rm -f

all: ejercicio_2 ejercicio_3

ejercicio_2.o: ejercicio_2.cpp
	${CC} -c ejercicio_2.cpp ${CPPFLAGS}
	
ejercicio_2: ejercicio_2.o
	${CC} ejercicio_2.o -o ejercicio_2 ${LDFLAGS}
#--------------------------------------------------------
ejercicio_3.o: ejercicio_3.cpp
	${CC} -c ejercicio_3.cpp ${CPPFLAGS}
	
ejercicio_3: ejercicio_3.o
	${CC} ejercicio_3.o -o ejercicio_3 ${LDFLAGS}
#--------------------------------------------------------
clean:
	${RM} ejercicio_2.o ejercicio_2
	${RM} ejercicio_3.o ejercicio_3
