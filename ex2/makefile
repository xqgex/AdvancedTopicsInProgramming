COMP = g++
#put all your object files here
SRC_DIR = src
BIN_DIR = bin
OBJS =  $(BIN_DIR)/Main.o $(BIN_DIR)/GameManager.o $(BIN_DIR)/GameManagerBoard.o \
	$(BIN_DIR)/PlayerAlgorithmAutoRPS.o $(BIN_DIR)/PlayerAlgorithmFileRPS.o

#The executabel filename DON'T CHANGE
EXEC = $(BIN_DIR)/ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
	rm -f $(OBJS)
#a rule for building a simple c++ source file
#use g++ -MM ./src/main.cpp to see dependencies
$(BIN_DIR)/Main.o:		  $(SRC_DIR)/Main.cpp 			$(SRC_DIR)/Main.h			$(SRC_DIR)/BoardRPS.h		$(SRC_DIR)/FightInfoRPS.h \
				  $(SRC_DIR)/GameManager.h		$(SRC_DIR)/JokerChange.h		$(SRC_DIR)/MoveRPS.h		$(SRC_DIR)/PiecePositionRPS.h \
				  $(SRC_DIR)/PlayerAlgorithmAutoRPS.h	$(SRC_DIR)/PlayerAlgorithmFileRPS.h	$(SRC_DIR)/GameManagerBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/GameManager.o:	  $(SRC_DIR)/GameManager.cpp 		$(SRC_DIR)/GameManager.h		$(SRC_DIR)/BoardRPS.h		$(SRC_DIR)/FightInfoRPS.h \
				  $(SRC_DIR)/GameManagerBoard.h		$(SRC_DIR)/GameParameters.h		$(SRC_DIR)/JokerChange.h	$(SRC_DIR)/MoveRPS.h \
				  $(SRC_DIR)/PiecePositionRPS.h		$(SRC_DIR)/PlayerAlgorithmAutoRPS.h	$(SRC_DIR)/PlayerAlgorithmFileRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/GameManagerBoard.o:    $(SRC_DIR)/GameManagerBoard.cpp	$(SRC_DIR)/GameManagerBoard.h		$(SRC_DIR)/BoardRPS.h \
				  $(SRC_DIR)/GameParameters.h		$(SRC_DIR)/PiecePositionRPS.h		$(SRC_DIR)/PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/PlayerAlgorithmAutoRPS.o: $(SRC_DIR)/PlayerAlgorithmAutoRPS.cpp $(SRC_DIR)/PlayerAlgorithmAutoRPS.h	$(SRC_DIR)/PlayerAlgorithm.h	$(SRC_DIR)/BoardRPS.h \
				  $(SRC_DIR)/FightInfoRPS.h		$(SRC_DIR)/GameParameters.h		 $(SRC_DIR)/JokerChangeRPS.h	$(SRC_DIR)/MoveRPS.h \
				  $(SRC_DIR)/PiecePositionRPS.h		$(SRC_DIR)/PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(BIN_DIR)/PlayerAlgorithmFileRPS.o: $(SRC_DIR)/PlayerAlgorithmFileRPS.cpp	$(SRC_DIR)/PlayerAlgorithmFileRPS.h	$(SRC_DIR)/PlayerAlgorithm.h	$(SRC_DIR)/BoardRPS.h \
				  $(SRC_DIR)/FightInfoRPS.h		$(SRC_DIR)/GameParameters.h		 $(SRC_DIR)/JokerChangeRPS.h	$(SRC_DIR)/MoveRPS.h \
				  $(SRC_DIR)/PiecePositionRPS.h		$(SRC_DIR)/PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
clean:
	rm -f $(OBJS) $(EXEC)
