#Autor: Piotr Piechowicz      20.03.2019r
#plik makefile do programow obslugujacych sygnaly
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = so3a
#program do obslugi sygnalow
NAME2 = so3b
#program wywolujacy program nr 1 poprzez exec i wysyla do niego sygnal
NAME3 = so3c
#program tworzacy proces potomny w ktorym uruchamiane programy nr 1 przy pomocy exec i wysylane sygnaly do wszystkich procesow potomnych
EXEC1  = $(NAME1).x
OBJS1  = $(NAME1).o
EXEC2  = $(NAME2).x
OBJS2  = $(NAME2).o
EXEC3  = $(NAME3).x
OBJS3  = $(NAME3).o
CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O
CO = gcc
LD = $(CO)
%.o: %.c
	$(CO) $(CFLAGS) -c $<
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)
$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: run1 
run1: $(EXEC1)
	./$(EXEC1) ${ARGS}
.PHONY: run2
run2: $(EXEC2) $(EXEC1)
	./$(EXEC2) ${ARGS}
.PHONY: run3
run3: $(EXEC3) $(EXEC1)
	./$(EXEC3) ${ARGS}
.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
