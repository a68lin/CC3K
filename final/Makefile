CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = myprogram
OBJECTS = main.o character.o dragon.o dwarf.o elf.o enemy.o goblin.o human.o merchant.o orc.o phoenix.o player.o troll.o vampire.o werewolf.o enemyFactory.o playerFactory.o
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
