OBJS = main.o game.o object.o objectsqueue.o objectslist.o player.o
CPPS = main.cpp game.cpp object.cpp objectsqueue.cpp objectslist.cpp player.cpp
all: compile link move
	
compile: 
	g++ -Isrc/include -c $(CPPS)

link:
	g++ $(OBJS) -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

move:
	move "main.exe" "Final\main.exe"
	xcopy "resources" "Final\resources"

run:
	Final/main.exe