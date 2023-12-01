CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -g
OBJECTS= main.o player.o computer.o human.o deck.o pile.o card.o subject.o board.o textobserver.o observer.o outputhelpers.o 
DEPENDS=${OBJECTS:.o=.d}
EXEC=straights

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
