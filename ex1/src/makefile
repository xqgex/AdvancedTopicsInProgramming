COMP = g++-5.3.0
#put all your object files here
OBJS = main.o main_aux.o game.o board.o
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp main_aux.h game.h board.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main_aux.o: main_aux.cpp main_aux.h game.h board.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
game.o: game.cpp game.h board.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
board.o: board.cpp board.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
