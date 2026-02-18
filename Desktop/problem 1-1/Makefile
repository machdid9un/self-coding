CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

COMMON_SIM_SRCS = Animal.cpp Herbivore.cpp Carnivore.cpp Utils.cpp SimulationHelper.cpp
SRCS_TEST = test.cpp $(COMMON_SIM_SRCS)
SRCS_SIM = simulate.cpp $(COMMON_SIM_SRCS)

OBJS_TEST = $(SRCS_TEST:.cpp=.o)
OBJS_SIM = $(SRCS_SIM:.cpp=.o)

all: test simulate

test: $(OBJS_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^

simulate: $(OBJS_SIM)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o test simulate

.PHONY: all clean
