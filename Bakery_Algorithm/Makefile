#Autor: Piotr Piechowicz      27.05.2019r
#plik makefile do programu obrazujacego algorytm piekarni
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = piekarnia
#program glowny zawierajacy wszsystkie polecenia z cw 9
EXEC1  = $(NAME1).x
OBJS1  = $(NAME1).o
CFLAGS = -Wall -O -fPIC -pthread
LFLAGS = -Wall -O
LDLIBS = -lpthread
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
