GAMEc=game.c
LCHRc=launcherinit.c
BUBINc=bubinit.c
HDLEc=handleevent.c
GAMEINITc=gameinit.c
STUCTh=../headers/struct.h
INITh=../headers/init.h
CONSTh=../headers/const.h
BUBh=../headers/bubble.h
BIN=game

$(BIN): $(STUCTh) $(INITh) $(CONSTh) $(BUBh) $(GAMEc) $(LCHRc) $(BUBINc) $(HDLEc) $(GAMEINITc)
	gcc -Wall -g -std=c99 $(STUCTh) $(INITh) $(CONSTh) $(BUBh) $(GAMEc) $(LCHRc) $(BUBINc) $(HDLEc) $(GAMEINITc) `sdl-config --cflags --libs` -o $(BIN) -lm

clean:
	rm -f $(BIN)