CXXFLAGS += -Wall -std=c++11
EXE = patients
OBJS = date.o patient.o medicine.o main.o

date.o: date.hh
patient.o: patient.hh
medicine.o: medicine.hh
main.o patient.o medicine.o: date.hh patient.hh medicine.hh main.cc
# side.o: side.hpp

.DEFAULT_GOAL = all

all: build

.PHONY: all build clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) *.o
	$(RM) $(EXE)

distclean: clean
	$(RM) *~
