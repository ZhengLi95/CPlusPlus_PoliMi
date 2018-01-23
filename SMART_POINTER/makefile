CXX = g++
CXXFLAGS += -Wall -std=c++11
EXE = main

all: $(EXE)
$(EXE): user.o place.o main.o comment.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cc place.hh user.hh
	$(CXX) $(CXXFLAGS) $< -c -o $@
user.o: user.cc user.hh
	$(CXX) $(CXXFLAGS) $< -c -o $@
place.o: place.cc place.hh
	$(CXX) $(CXXFLAGS) $< -c -o $@
comment.o: comment.cc comment.hh
	$(CXX) $(CXXFLAGS) $< -c -o $@

clean:
	$(RM) *.o
	$(RM) $(EXE)
distclean: clean
	$(RM) *~