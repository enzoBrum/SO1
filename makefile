CXX = g++
CXXFLAGS = -Wall -O2 -std=c++20

SRCS = $(shell find . -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)

TARGET = main

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)