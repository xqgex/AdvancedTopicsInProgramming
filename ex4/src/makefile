COMP = g++#-5.3.0

OBJS =		main.o
EXEC =		ex4

CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -g3

default:
	make all
$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
	rm -f *.o

main.o:	main.cpp	unit_test_util.h	ex4_header.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<

all: $(EXEC) $(OBJS)
clean:
	rm -f *.o $(EXEC)
