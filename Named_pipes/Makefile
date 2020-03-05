#Autor: Piotr Piechowicz      27.03.2019r
#plik makefile do programow obslugujacyh problem producent konsument w potokach FIFO
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = so5pa
#program otwierajacy plik zrodlowy i tworzacy potok nazwany do ktorego przesyla dane
NAME2 = so5ka
#program otwierajacy potok stworzony przez program so5pa oraz przesylajacy dane do pliku wyjsciowego
NAME3 = so5pb
#program producent otwierajacy potok ktorego sciezke i nazwe otrzymuje jako argument i zapisujacy do niego dane
NAME4 = so5kb
#program konsument zapisujacy dane do pliku wyjsciowego z potoku nazwanego ktorego sciezke otrzymuje jako argument
POTOK = PTK
#zmienna na nazwe potoku
EXEC1  = $(NAME1).x
OBJS1  = $(NAME1).o
EXEC2  = $(NAME2).x
OBJS2  = $(NAME2).o
EXEC3  = $(NAME3).x
OBJS3  = $(NAME3).o
EXEC4  = $(NAME4).x
OBJS4  = $(NAME4).o
CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O
CO = gcc
LD = $(CO)
%.o: %.c
	$(CO) $(CFLAGS) -c $<
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)
$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: run1 
run1: $(EXEC1) $(EXEC2)
	./$(EXEC1)
	diff -s Source Output
	rm fifo
.PHONY: run2
run2: $(EXEC3) $(EXEC4)
	mkfifo -m 666 $(POTOK)
	xterm -hold -title producent -e ./$(EXEC3) $(POTOK) &
	xterm -hold -title konsument -e ./$(EXEC4) $(POTOK) 
	rm $(POTOK)
	diff -s Source Output
.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
