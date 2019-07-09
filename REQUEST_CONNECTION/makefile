EXE = exe 
OBJECTS = connection.o request.o main.o
CXXFLAGS += -std=c++11 -Wall

all : $(EXE)

$(EXE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

connection.o : connection.h
request.o : request.h
main.o : connection.h request.h

.PHONY: all clean distclean
clean:
	$(RM) *.o 
distclean:
	$(RM) $(EXE)