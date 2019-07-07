CXXFLAGS += -Wall std=c++11

EXE = main

OBJS = main.o smallerinputfirstqueue.o timeoutqueue.o queue.o task.OBJS

main.o smallerinputfirstqueue.o timeoutqueue.o queue.o task.o : task.hpp
main.o smallerinputfirstqueue.o timeoutqueue.o queue.o : queue.hpp
main.o smallerinputfirstqueue.o : smallerinputfirstqueue.hpp
main.o timeoutqueue.o : timeoutqueue.hpp

.DEFAULT_GOAL = all
.PHONY: all build clean distclean

all: build

build: $(EXE)

$(EXE) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)
	$(RM) *~