CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS= -lm
EXEC=main

all: $(EXEC)

$(EXEC): main.o piece.o plateau.o partie.o joueur.o
	$(CC) -o main main.o piece.o plateau.o partie.o joueur.o  $(LDFLAGS)

main.o: main.cpp plateau.hpp piece.hpp partie.hpp joueur.hpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

partie.o: partie.cpp partie.hpp
	$(CC) -o partie.o -c partie.cpp  $(CFLAGS)

joueur.o: joueur.cpp joueur.hpp
	$(CC) -o joueur.o -c joueur.cpp  $(CFLAGS)

plateau.o: plateau.cpp plateau.hpp
	$(CC) -o plateau.o -c plateau.cpp $(CFLAGS)

piece.o: piece.cpp piece.hpp
	$(CC) -o piece.o -c piece.cpp  $(CFLAGS)






clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)





