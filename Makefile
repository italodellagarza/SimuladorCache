# Arquivo makefile

CPP	=	g++
CPPFLAGS	=	-Wall -Wconversion
OBJ	=	obj/Main.o obj/Memory.o obj/MainMemory.o obj/Processor.o obj/Cache.o obj/TACache.o obj/SACache.o

all:	SimuladorCache

SimuladorCache:	$(OBJ)
	$(CPP) $(CPPFLAGS) obj/*.o -o bin/SimuladorCache

obj/Main.o:	src/Main.cpp
	if ! [ -d "obj/" ]; then mkdir obj; fi
	if ! [ -d "bin/" ]; then mkdir bin; fi
	$(CPP) $(CPPFLAGS) -c src/Main.cpp -o obj/Main.o

obj/MainMemory.o:	src/MainMemory.cpp	src/MainMemory.h
	$(CPP) $(CPPFLAGS) -c src/MainMemory.cpp -o obj/MainMemory.o

obj/Memory.o:	src/Memory.cpp	src/Memory.h
	$(CPP) $(CPPFLAGS) -c src/Memory.cpp -o obj/Memory.o

obj/Processor.o:	src/Processor.cpp	src/Processor.h
	$(CPP) $(CPPFLAGS) -c src/Processor.cpp -o obj/Processor.o

obj/Cache.o:	src/Cache.cpp	src/Cache.h
	$(CPP) $(CPPFLAGS) -c src/Cache.cpp -o obj/Cache.o

obj/TACache.o:	src/TACache.cpp	src/TACache.h
	$(CPP) $(CPPFLAGS) -c src/TACache.cpp -o obj/TACache.o

obj/SACache.o:	src/SACache.cpp	src/SACache.h
	$(CPP) $(CPPFLAGS) -c src/SACache.cpp -o obj/SACache.o

clean:
	rm -rf obj/ bin/