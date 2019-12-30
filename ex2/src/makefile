COMP = g++-5.3.0
#put all your object files here
OBJS =  Main.o GameManager.o GameManagerBoard.o PlayerAlgorithmAutoRPS.o PlayerAlgorithmFileRPS.o

#The executabel filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
Main.o:			Main.cpp 			Main.h				BoardRPS.h		FightInfoRPS.h \
			GameManager.h			JokerChange.h			MoveRPS.h		PiecePositionRPS.h \
			PlayerAlgorithmAutoRPS.h	PlayerAlgorithmFileRPS.h	GameManagerBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o:		GameManager.cpp 		GameManager.h			BoardRPS.h		FightInfoRPS.h \
			GameManagerBoard.h		GameParameters.h		JokerChange.h		MoveRPS.h \
			PiecePositionRPS.h		PlayerAlgorithmAutoRPS.h	PlayerAlgorithmFileRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManagerBoard.o:	GameManagerBoard.cpp		GameManagerBoard.h		BoardRPS.h		GameParameters.h \
			PiecePositionRPS.h		PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PlayerAlgorithmAutoRPS.o: PlayerAlgorithmAutoRPS.cpp	PlayerAlgorithmAutoRPS.h	PlayerAlgorithm.h	BoardRPS.h \
			  FightInfoRPS.h		GameParameters.h		JokerChangeRPS.h	MoveRPS.h \
			  PiecePositionRPS.h		PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PlayerAlgorithmFileRPS.o: PlayerAlgorithmFileRPS.cpp	PlayerAlgorithmFileRPS.h	PlayerAlgorithm.h	BoardRPS.h \
			  FightInfoRPS.h		GameParameters.h		JokerChangeRPS.h	MoveRPS.h \
			  PiecePositionRPS.h		PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
