.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = so1a
NAME2 = so1b
NAME3 = so1c
NAME4 = so1d
NAME5 = so1e
EXEC1  = $(NAME1).x  
OBJS1  = $(NAME1).o
EXEC2  = $(NAME2).x  
OBJS2  = $(NAME2).o
EXEC3  = $(NAME3).x  
OBJS3  = $(NAME3).o
EXEC4  = $(NAME4).x  
OBJS4  = $(NAME4).o
EXEC5  = $(NAME5).x  
OBJS5  = $(NAME5).o
CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O
CO = gcc
LD = $(CO)
%.o: %.c
	$(CO) $(CFLAGS) -c $<
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
$(EXEC1): $(OBJS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC4): $(OBJS4) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC5): $(OBJS5) 
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: run1 run2 run3 run4 run5
run1: $(EXEC1)
	./$(EXEC1)
run2: $(EXEC2)
	./$(EXEC2)
run3: $(EXEC3)
	./$(EXEC3); sleep 5	
run4: $(EXEC4)
	./$(EXEC4)		
run5: $(EXEC5)
	./$(EXEC5)	
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out;
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )	
	
	
	
	






