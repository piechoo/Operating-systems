#Autor: Piotr Piechowicz      24.04.2019r
#plik makefile do programow obslugujacyh semafory
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = so6
#program powielajacy program do obslugi sygnalow w kombinacji fork-exec
NAME2 = so6p
#program obslugujacy semafory
NAME3 = so6f
#biblioteka funkcji obslugujacych semafory
NAME4 = so6f.h
#naglowek biblioteki funkcji obslugujacych semafory
EXEC1  = $(NAME1).x
OBJS1  = $(NAME1).o
EXEC2  = $(NAME2).x
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
CFLAGS = -Wall -O -fPIC -pthread
LFLAGS = -Wall -O
CO = gcc
LD = $(CO)
.PHONY: all
all: $(EXEC1) $(EXEC2)
$(EXEC1):$(NAME4) $(OBJS3) $(OBJS1)
	$(CO) $(CFLAGS) $(NAME4) $(OBJS3) $(OBJS1) -o $@
$(EXEC2):$(NAME4) $(OBJS3) $(OBJS2)
	$(CO) $(CFLAGS) $(NAME4) $(OBJS3) $(OBJS2) -o $@
.PHONY: run1 
run1: $(EXEC1) $(EXEC2) 
	./$(EXEC1) $(EXEC2) ${ARGS}
.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
