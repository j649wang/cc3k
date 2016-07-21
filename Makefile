CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k
OBJECTS = main.o ba.o bd.o cell.o chamber.o character.o component.o display.o dragon.o dragonHoard.o dwarf.o elves.o enemy.o floor.o game.o goblin.o gold.o human.o item.o merchant.o merchantHoard.o smallHoard.o normalHoard.o orc.o ph.o phoenix.o player.o potion.o rh.o troll.o vampire.o wa.o wd.o werewolf.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
