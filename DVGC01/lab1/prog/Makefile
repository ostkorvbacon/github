
OFILES =  Dkeytoktab.o keytoktab.o
tkeytoktab: $(OFILES)
	gcc -Wall -o tkeytoktab Dkeytoktab.o keytoktab.o

Dkeytoktab.o: Dkeytoktab.c keytoktab.h
	gcc -Wall -c Dkeytoktab.c

keytoktab.o: keytoktab.c keytoktab.h
	gcc -Wall -c keytoktab.c

clean:
	rm tkeytoktab
	rm $(OFILES)
