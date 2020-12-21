
OFILES = lab4.o finfile.o foutfile.o
lab4: $(OFILES)
	gcc -Wall -o lab4 lab4.o finfile.o foutfile.o
lab4.o: lab4.c lab4.h
	gcc -c lab4.c
finfile.o: finfile.c lab4.h
	gcc -c finfile.c
foutfile.o: foutfile.c lab4.h
	gcc -c foutfile.c
clean:
	rm lab4
	rm $(OFILES)
