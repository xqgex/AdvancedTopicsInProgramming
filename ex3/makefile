COMP = g++
SRC_DIR = src
BIN_DIR = bin

OBJS =  $(BIN_DIR)/TournamentManager.o	$(BIN_DIR)/AlgorithmRegistration.o	$(BIN_DIR)/GameManagerBoard.o \
	$(BIN_DIR)/GameManager.o
OUR_O = $(BIN_DIR)/RSPPlayer_mycode.o
OUR_SO = $(BIN_DIR)/RSPPlayer_mycode.so
EXEC = $(BIN_DIR)/ex3

CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -g3
EXEC_LINK_FLAG = -rdynamic -ldl -pthread -g3
SO_COMP_FLAG = -mcmodel=large

default:
	make all
$(EXEC): $(OBJS)
	$(COMP) $(EXEC_LINK_FLAG) $(OBJS) -o $@
	rm -f $(BIN_DIR)/*.o

#Hint: A rule for building a simple c++ source file: Use g++ -MM ./TournamentManager.cpp to see dependencies
$(BIN_DIR)/TournamentManager.o:	src/TournamentManager.cpp			$(SRC_DIR)/TournamentManager.h		$(SRC_DIR)/AlgorithmRegistration.h	$(SRC_DIR)/GameParameters.h \
				$(SRC_DIR)/GameManager.h			$(SRC_DIR)/GameManagerBoard.h		$(SRC_DIR)/BoardRPS.h			$(SRC_DIR)/FightInfoRPS.h \
				$(SRC_DIR)/JokerChangeRPS.h			$(SRC_DIR)/MoveRPS.h			$(SRC_DIR)/PiecePositionRPS.h		$(SRC_DIR)/PointRPS.h \
				$(SRC_DIR)/PlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/AlgorithmRegistration.o: $(SRC_DIR)/AlgorithmRegistration.cpp $(SRC_DIR)/PlayerAlgorithm.h			$(SRC_DIR)/TournamentManager.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/GameManager.o:	$(SRC_DIR)/GameManager.cpp 			$(SRC_DIR)/GameManager.h		$(SRC_DIR)/BoardRPS.h			$(SRC_DIR)/FightInfoRPS.h \
				$(SRC_DIR)/GameManagerBoard.h			$(SRC_DIR)/GameParameters.h		$(SRC_DIR)/JokerChange.h		$(SRC_DIR)/MoveRPS.h \
				$(SRC_DIR)/PiecePositionRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/GameManagerBoard.o:	$(SRC_DIR)/GameManagerBoard.cpp			$(SRC_DIR)/GameManagerBoard.h		$(SRC_DIR)/BoardRPS.h \
				$(SRC_DIR)/GameParameters.h			$(SRC_DIR)/PiecePositionRPS.h		$(SRC_DIR)/PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(OUR_O): 			$(SRC_DIR)/RSPPlayer_mycode.cpp		$(SRC_DIR)/RSPPlayer_mycode.h	$(SRC_DIR)/PlayerAlgorithm.h		$(SRC_DIR)/BoardRPS.h \
				$(SRC_DIR)/FightInfoRPS.h			$(SRC_DIR)/GameParameters.h		$(SRC_DIR)/JokerChangeRPS.h		$(SRC_DIR)/MoveRPS.h \
				$(SRC_DIR)/PiecePositionRPS.h			$(SRC_DIR)/PointRPS.h			$(SRC_DIR)/AlgorithmRegistration.h
	$(COMP) -c $(SRC_DIR)/RSPPlayer_mycode.cpp $(CPP_COMP_FLAG) $(SO_COMP_FLAG) -o $(OUR_O)
$(OUR_SO): $(OUR_O)
	$(COMP) -shared -g3 -Wl,-soname,$(OUR_SO) -o $(OUR_SO) $(OUR_O)
	rm -f $(BIN_DIR)/*.o

all: $(EXEC) $(OBJS) $(OUR_SO) $(OUR_O)
rps_tournament: $(EXEC) $(OBJS)
rps_lib: $(OUR_SO) $(OUR_O)
clean:
	rm -f $(BIN_DIR)/*.o $(OUR_SO) $(EXEC)
