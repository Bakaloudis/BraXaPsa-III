
output: CandyCrash.o
	gcc CandyCrash.o -lglut -lGL -lGLU -lstdc++ -o output

CandyCrash.o: CandyCrash.cpp
	gcc -c CandyCrash.cpp 

clean:
	rm *.o output

