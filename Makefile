COMPILER = g++
OPTIONS = -I include -L lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -o main 
SRCS = src/main.cpp src/character.cpp src/skeleton.cpp src/menu.cpp

all:
	${COMPILER} ${SRCS} ${OPTIONS}

run:
	${COMPILER} ${SRCS} ${OPTIONS}
	./main.exe

clean:
	del main.exe