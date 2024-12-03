CXX=g++
RM=rm -f
OBJS=fixComp.cpp

all: fixcomp
	./fixcomp

fixcomp: $(OBJS)
	$(CXX) --std=c++17 -o fixcomp $(OBJS)

clean:
	$(RM) fixcomp
