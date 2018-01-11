CXX = g++
CXXFLAGS += -Wall
EXE = main

all: $(EXE)
main: main.o fibonacci.o
	$(CXX) $(CXXFLAGS) $^ -o $@
main.o: main.cpp fibonacci.h
	$(CXX) $(CXXFLAGS) $< -c -o $@
fibonacci.o: fibonacci_iterative.cpp fibonacci.h
	$(CXX) $(CXXFLAGS) $< -c -o $@
clean:
	$(RM) *.o
distclean: clean
	$(RM) main