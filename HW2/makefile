Hw2.exe: lightmap.o Hw2.o
	 g++ -std=c++17 -o $@ $^ `root-config --cflags --libs`

lightmap.o: lightmap.cpp
	 g++ -std=c++17 -c $<

Hw2.o: Hw2.cpp
	g++ -std=c++17 -c $< `root-config --cflags --libs`

clean_all:
	 rm *.o *.exe

clean:
	rm *.exe

