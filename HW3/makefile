
EIGEN_INC := $(shell pkg-config eigen3 --cflags)

Hw3.exe: FCmatrixAlgo.o EqSolver.o Hw3.o
	g++ -std=c++17 -o $@ $^ `root-config --cflags --libs` $(EIGEN_INC)

FCmatrixAlgo.o: FCmatrixAlgo.cpp
	g++ -std=c++17 -c $^ $(EIGEN_INC)

EqSolver.o: EqSolver.cpp
	g++ -std=c++17 -c $^ $(EIGEN_INC)

Hw3.o: Hw3.cpp
	g++ -std=c++17 -c $< `root-config --cflags --libs` $(EIGEN_INC)

clean_all:
	 rm *.o *.exe

clean:
	rm *.exe
