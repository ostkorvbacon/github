
OFILES1 =  driver.o parser.o
OFILES2 =  Dkeytoktab.o keytoktab.o

all: parser tkeytoktab

parser: $(OFILES1) keytoktab.o
	gcc -Wall -o parser driver.o parser.o keytoktab.o

tkeytoktab: $(OFILES2)
	gcc -Wall -o tkeytoktab Dkeytoktab.o keytoktab.o

driver.o: driver.c parser.h
	gcc -Wall -c driver.c

parser.o: parser.c keytoktab.h
	gcc -Wall -c parser.c

Dkeytoktab.o: Dkeytoktab.c keytoktab.h
	gcc -Wall -c Dkeytoktab.c

keytoktab.o: keytoktab.c keytoktab.h
	gcc -Wall -c keytoktab.c


clean:
	rm parser
	rm tkeytoktab
	rm $(OFILES1)
	rm $(OFILES2)
