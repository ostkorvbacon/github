OFILES = driv.o list.o

huvud:	huvud.o	driv.o	list.o
	gcc	-o	huvud huvud.o driv.o list.o

huvud.o: huvud.c driv.h
	gcc -c huvud.c

driv.o:	driv.c	driv.h
	gcc	-c	driv.c

list.o:	list.c	list.h
	gcc	-c	list.c
clean:
	rm huvud
	rm $(OFILES)
