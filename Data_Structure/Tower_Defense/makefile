towerDefence : towerDefence.o rank.o enemy.o towerMap.o event.o help.o
	gcc -o towerDefence towerDefence.o rank.o enemy.o towerMap.o event.o help.o -lncurses

towerDefence.o : towerDefence.c towerDefence.h
	gcc -c towerDefence.c -lncurses

rank.o : rank.c towerDefence.h
	gcc -c rank.c -lncurses

enemy.o : enemy.c towerDefence.h
	gcc -c enemy.c -lncurses

towerMap.o : towerMap.c towerDefence.h
	gcc -c towerMap.c -lncurses

event.o : event.c towerDefence.h
	gcc -c event.c -lncurses

help.o : help.c towerDefence.h
	gcc -c help.c -lncurses

rm :
	rm towerDefence *.o
