# Arquivo makefile

CPP	=	g++
CPPFLAGS	=	-Wall -Wconversion

# TODO Criar as pastas que não existem

all:	Main

Main:	obj/Main.o
	$(CPP) $(CPPFLAGS) obj/Main.o -o bin/Main

obj/Main.o:	src/Main.cpp
	$(CPP) $(CPPFLAGS) -c src/Main.cpp -o obj/Main.o

clean:
	rm -rf obj/ bin/