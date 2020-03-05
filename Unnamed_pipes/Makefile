#Autor: Piotr Piechowicz      27.03.2019r
#plik makefile do programow obslugujacyh problem producent konsument
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = so4p
#program otwierajacy plik zrodlowy i przesylajacy dane do potoku
NAME2 = so4k
#program otwierajacy potok oraz przesylajacy dane do pliku wyjsciowego
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
run1: $(EXEC1) $(EXEC2)
	./$(EXEC1) 
	diff -s Source Output
.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
