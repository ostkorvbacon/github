OFILES1 =  driver.o parser.o
OFILES2 =  Dkeytoktab.o keytoktab.o
OFILES3 =  Dlexer.o lexer.o
OFILES4 =  Dsymtab.o symtab.o
OFILES5 = Doptab.o optab.o
all: parser tkeytoktab tlexer tsymtab toptab
parser: $(OFILES1) keytoktab.o lexer.o symtab.o optab.o
	gcc -Wall -o parser driver.o parser.o keytoktab.o lexer.o symtab.o optab.o
tkeytoktab: $(OFILES2)
	gcc -Wall -o tkeytoktab Dkeytoktab.o keytoktab.o
tlexer: $(OFILES3) keytoktab.o
	gcc -Wall -o tlexer Dlexer.o lexer.o keytoktab.o
tsymtab: $(OFILES4) keytoktab.o
	gcc -Wall -o tsymtab Dsymtab.o symtab.o keytoktab.o
toptab: $(OFILES5) keytoktab.o
	gcc -Wall -o toptab Doptab.o optab.o keytoktab.o

driver.o: driver.c parser.h
	gcc -Wall -c driver.c
parser.o: parser.c keytoktab.h
	gcc -Wall -c parser.c
Dkeytoktab.o: Dkeytoktab.c keytoktab.h
	gcc -Wall -c Dkeytoktab.c
keytoktab.o: keytoktab.c keytoktab.h
	gcc -Wall -c keytoktab.c
Dlexer.o: Dlexer.c lexer.h
	gcc -Wall -c Dlexer.c
lexer.o: lexer.c keytoktab.h
	gcc -Wall -c lexer.c
Dsymtab.o: Dsymtab.c keytoktab.h symtab.h
	gcc -Wall -c Dsymtab.c
symtab.o: symtab.c keytoktab.h
	gcc -Wall -c symtab.c
Doptab.o: Doptab.c optab.h keytoktab.h
	gcc -Wall -c Doptab.c
optab.o: optab.c keytoktab.h
	gcc -Wall -c optab.c
clean:
	rm parser
	rm tkeytoktab
	rm tlexer
	rm toptab
	rm $(OFILES1)
	rm $(OFILES2)
	rm $(OFILES3)
	rm $(OFILES4)
	rm $(OFILES5)
