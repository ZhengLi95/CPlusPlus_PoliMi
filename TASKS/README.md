# TASKS

You have to develop a library to ease the development of a real-time system that executes tasks. Class `Task` is already implemented and it provides methods to access the input data set, its creation date (saved as `std::time_t`) and to run the task. The library must provide two classes for implementing the queues of tasks to be executed: `SmallerInputFirstQueue` and `TimeoutQueue`. Each queue stores tasks in a sorted `std::vector` and provides
three main functionalities:

+ `enqueue` adds a task to the queue;
+ `execute` removes and runs the first task in the queue and returns the result of the manipulation (a vector of integers);
+ `empty` checks if the queue contains no elements.

The two types of queue use different criteria to sort the tasks within the enqueue method. `SmallerInputFirstQueue` sorts tasks considering the size of the input data set. On the other hand, `TimeoutQueue` is a FIFO queue that stores tasks according to their creation times and uses a timeout (type `std::time_t`) to discard the tasks that will eventually expire before they can be executed. Class TimeoutQueue removes expired tasks when method execute or method empty are executed.

In particular, you have to:
1. Elaborate a solution for implementing the aforementioned queues by providing the necessary class declarations in one or more header file(s). It is not required to implement their methods. Feel free to add your own assumptions but motivate your choices.
2. Complete the Makefile showed below considering that the main function (defined in file `main.cpp`) instantiates and uses objects of both the types of queues.

```make
CXXFLAGS += -Wall -std=c++11
EXE = main
# TODO: DEFINE VARIABLE ‘OBJS’ AND FILE DEPENDENCIES HERE
.DEFAULT_GOAL = all
.PHONY: all build clean distclean
all: build
build: $(EXE)
$(EXE): $(OBJS)
$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)
clean:
$(RM) $(OBJS)
distclean: clean
$(RM) $(EXE)
$(RM) *~
```