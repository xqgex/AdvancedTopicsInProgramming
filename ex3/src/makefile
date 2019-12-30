COMP = g++-5.3.0

OBJS =		TournamentManager.o AlgorithmRegistration.o GameManagerBoard.o GameManager.o
OUR_O =		RSPPlayer_mycode.o
OUR_SO =	RSPPlayer_mycode.so
EXEC =		ex3

CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -g3
EXEC_LINK_FLAG = -rdynamic -ldl -pthread -g3
SO_COMP_FLAG = -mcmodel=large

default:
	make all
$(EXEC): $(OBJS)
	$(COMP) $(EXEC_LINK_FLAG) $(OBJS) -o $@
	rm -f *.o

#Hint: A rule for building a simple c++ source file: Use g++ -MM ./TournamentManager.cpp to see dependencies
TournamentManager.o:	TournamentManager.cpp		TournamentManager.h		AlgorithmRegistration.h		GameParameters.h \
			GameManager.h			GameManagerBoard.h		BoardRPS.h			FightInfoRPS.h \
			JokerChangeRPS.h		MoveRPS.h			PiecePositionRPS.h		PointRPS.h \
			PlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
AlgorithmRegistration.o: AlgorithmRegistration.cpp	PlayerAlgorithm.h		TournamentManager.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
GameManager.o:		GameManager.cpp 		GameManager.h			BoardRPS.h			FightInfoRPS.h \
			GameManagerBoard.h		GameParameters.h		JokerChange.h			MoveRPS.h \
			PiecePositionRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
GameManagerBoard.o:	GameManagerBoard.cpp		GameManagerBoard.h		BoardRPS.h \
			GameParameters.h		PiecePositionRPS.h		PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c -o $@ $<
$(OUR_O): 		RSPPlayer_mycode.cpp		RSPPlayer_mycode.h		PlayerAlgorithm.h		BoardRPS.h \
			FightInfoRPS.h			GameParameters.h		JokerChangeRPS.h		MoveRPS.h \
			PiecePositionRPS.h		PointRPS.h			AlgorithmRegistration.h
	$(COMP) -c RSPPlayer_mycode.cpp $(CPP_COMP_FLAG) $(SO_COMP_FLAG) -o $(OUR_O)
$(OUR_SO): $(OUR_O)
	$(COMP) -shared -g3 -Wl,-soname,$(OUR_SO) -o $(OUR_SO) $(OUR_O)
	rm -f *.o

all: $(EXEC) $(OBJS) $(OUR_SO) $(OUR_O)
rps_tournament: $(EXEC) $(OBJS)
rps_lib: $(OUR_SO) $(OUR_O)
clean:
	rm -f *.o $(OUR_SO) $(EXEC)
