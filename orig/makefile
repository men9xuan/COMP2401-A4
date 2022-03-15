OBJ = display.o rrtMaker.o rrtTester.o
OUT = rrtTester
all: 	display rrtMaker main
	gcc -o $(OUT) $(OBJ) -lm -lX11

display: 	display.c display.h obstacles.h
	gcc -c display.c -lm -lX11

rrtMaker: 	rrtMaker.c obstacles.h display.h
	gcc -c rrtMaker.c -lm -lX11

main: rrtTester.c display.h obstacles.h
	gcc -c rrtTester.c -lm -lX11

clean:
	rm -f *.o

cleanall:
	rm -f *.o
	rm -f $(OUT)