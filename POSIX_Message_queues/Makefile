#Autor: Piotr Piechowicz      23.05.2019r
#plik makefile do programow obslugujacyh problem klient serwer
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = serwer
#program serwer wykonujacy dzialanie
NAME2 = klient
#program klient wysylajacy dzialanie do serwera
NAME3 = kolejki
#biblioteka funkcji kolejek
NAME4 = kolejki.h
#plik naglowkowy funkcji kolejek
EXEC1  = $(NAME1).x
OBJS1  = $(NAME1).o
EXEC2  = $(NAME2).x
OBJS2  = $(NAME2).o
EXEC3  = $(NAME3).x
OBJS3  = $(NAME3).o
CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O
LDLIBS = -lrt
CO = gcc
LD = $(CO)
%.o: %.c
	$(CO) $(CFLAGS) -c $<
.PHONY: all
all: $(EXEC1) $(EXEC2)
$(EXEC1): $(OBJS1) $(OBJS3)
	$(LD) $(OBJS1) $(NAME4) $(OBJS3) -o $@ $(LFLAGS) $(LDLIBS)
$(EXEC2): $(OBJS2) $(OBJS3)
	$(LD) $(OBJS2) $(NAME4) $(OBJS3) -o $@ $(LFLAGS) $(LDLIBS) 
.PHONY: run
run: $(EXEC1) $(EXEC2)
	xterm -hold -title SERWER -bg red -e ./$(EXEC1) &
	xterm -hold -title KLIENT1 -bg blue -e ./$(EXEC2) &
	xterm -hold -title KLIENT2 -bg blue -e ./$(EXEC2) &
.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
