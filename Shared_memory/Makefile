#Autor: Piotr Piechowicz      14.05.2019r
#plik makefile do programow obslugujacyh pamiec dzielona
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = so7
#program powielajacy program do obslugi sygnalow w kombinacji fork-exec
NAME2 = so7k
#program obslugujacy semafory
NAME3 = semafory
#biblioteka funkcji obslugujacych semafory
NAME4 = semafory.h
#naglowek biblioteki funkcji obslugujacych semafory
NAME5 = pamiec
#biblioteka funkcji obslugujacych pamiec
NAME6 = pamiec.h
#naglowek biblioteki pamieci
EXEC1s  = $(NAME1).x
EXEC1d  = $(NAME1)d.x
EXEC1d2  = $(NAME1)d2.x
OBJS1  = $(NAME1).o
EXEC2s  = $(NAME2).x
EXEC2d  = $(NAME2)d.x
EXEC2d2  = $(NAME2)d2.x
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS5  = $(NAME5).o
#naglowek biblioteki funkcji obslugujacych semafory
LIB_NAME = MojeFunkcje
# Katalog dla bibliotek
LIB_DIR = ./lib
# Biblioteka statyczna (static library)
LIB_STAT = lib$(LIB_NAME).a
# Biblioteka dzielona (shared library)
LIB_SHAR = lib$(LIB_NAME).so
# Pliki objectowe wchodzace do biblioteki
LIB_OBJS = $(OBJS3) $(OBJS5)
# Pliki naglowkowe
HEADS2 = 
HEADS3 = $(NAME3).h $(NAME5).h
CFLAGS = -Wall -O -fPIC -pthread
LFLAGS = -Wall -O -fPIC -pthread
CO = gcc
LD = $(CO)
AR = ar
LDLIBS= -lrt
ARFLAGS = rv
.PHONY: all
all: $(EXEC1s) $(EXEC2s) $(EXEC1d) $(EXEC2d) $(EXEC1d2) $(EXEC2d2)
# Tworzenie biblioteki statycznej
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)
# Tworzenie biblioteki dzielonej
$(LIB_SHAR): $(LIB_OBJS)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)
#kompilacja z biblioteka statyczna
$(EXEC1s): $(OBJS1) $(OBJS3) $(OBJS5) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
$(EXEC2s): $(OBJS2) $(OBJS3) $(OBJS5) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
#kompilacja z biblioteka dynamiczna v1     
$(EXEC1d): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
$(EXEC2d): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
#kompilacja z biblioteka dynamiczna v2
$(EXEC1d2): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
$(EXEC2d2): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
#uruchamianie z biblioteka statyczna
.PHONY: runs
runs: $(EXEC1s) $(EXEC2s)
	./$(EXEC1s) $(EXEC2s)
	diff -s Source Output
#uruchamianie z biblioteka dynamiczna v1
.PHONY: rund1
rund1: $(EXEC1d) $(EXEC2d)
	./$(EXEC1d) $(EXEC2d)
	diff -s Source Output
#uruchamianie z biblioteka dynamiczna v2
.PHONY: rund2
rund2: $(EXEC1d2) $(EXEC2d2)
	( export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC1d2) $(EXEC2d2))
	diff -s Source Output
.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
