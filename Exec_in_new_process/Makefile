#Autor: Piotr Piechowicz      13.03.2019r
#plik makefile do programu wykorzystujacego fork-exec
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = so1a
#program wywolywany przez exec
NAME2 = so1exec
#program wywolujacy exec
EXEC1  = $(NAME1).x
OBJS1  = $(NAME1).o
EXEC2  = $(NAME2).x
OBJS2  = $(NAME2).o
CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O
CO = gcc
LD = $(CO)
%.o: %.c
	$(CO) $(CFLAGS) -c $<
.PHONY: all
all: $(EXEC1) $(EXEC2)
$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: run1 
run1: $(EXEC2) $(EXEC1)
	./$(EXEC2) $(EXEC1)
.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
