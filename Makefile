EIGEN_INC := $(shell pkg-config eigen3 --cflags)
ROOT_INC := -I$(shell root-config --cflags)
ROOT_LIBS := $(shell root-config --libs)

%.exe: %.C
	g++ -std=c++17 $< -o $@ $(EIGEN_INC) $(ROOT_INC) $(ROOT_LIBS)

