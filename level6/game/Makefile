GAMEc=game.c
STUCTh=../headers/struct.h
INITh=../headers/init.h
CONSTh=../headers/const.h
BUBh=../headers/bubble.h
BIN=game

$(BIN): $(STUCTh) $(INITh) $(CONSTh) $(BUBh) $(GAMEc)
	gcc -Wall -g -std=c99 $(STUCTh) $(INITh) $(CONSTh) $(BUBh) $(GAMEc) `sdl-config --cflags --libs` -o $(BIN) -lm

clean:
	rm -f $(BIN)