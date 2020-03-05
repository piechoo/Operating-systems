#Autor: Piotr Piechowicz      26.05.2019r
#plik makefile do programow obslugujacyh watki i mutexy
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = watki
#program glowny zawierajacy wszsystkie polecenia z cw 9
EXEC1  = $(NAME1).x
OBJS1  = $(NAME1).o
CFLAGS = -Wall -O -fPIC -pthread
LFLAGS = -Wall -O
LDLIBS = -lrt
CO = gcc
LD = $(CO)
.PHONY: all
all: $(EXEC1)
$(EXEC1):$(OBJS1)
	$(CO) $(CFLAGS) $(OBJS1) -o $@ $(LDLIBS)
.PHONY: run
run: $(EXEC1)
	./$(EXEC1)
.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
