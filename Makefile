OUT = cat-c cat-c++ cat.class

all: $(OUT)

clean:
	rm -f $(OUT)

cat-c: cat.c
	$(CC) -g -Wall -O3 -o cat-c cat.c

cat-c++: cat.cpp
	$(CXX) -g -Wall -O3 -o cat-c++ cat.cpp

cat.class: cat.java
	javac cat.java
