COMP = g++
#put all your object files here
SRC_DIR = src
BIN_DIR = bin
OBJS = $(BIN_DIR)/main.o $(BIN_DIR)/main_aux.o $(BIN_DIR)/game.o $(BIN_DIR)/board.o
#The executabel filename DON'T CHANGE
EXEC = $(BIN_DIR)/ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
	rm -f $(OBJS)
#a rule for building a simple c++ source file
#use g++ -MM ./src/main.cpp to see dependencies
$(BIN_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/main_aux.h $(SRC_DIR)/game.h $(SRC_DIR)/board.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/main_aux.o: $(SRC_DIR)/main_aux.cpp $(SRC_DIR)/main_aux.h $(SRC_DIR)/game.h $(SRC_DIR)/board.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/game.o: $(SRC_DIR)/game.cpp $(SRC_DIR)/game.h $(SRC_DIR)/board.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/board.o: $(SRC_DIR)/board.cpp $(SRC_DIR)/board.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
clean:
	rm -f $(OBJS) $(EXEC)
