PROG=learn.prog
TEST=compute.prog
CXXFLAGS=-Wall -Wextra -pedantic -std=c++11 `pkg-config --cflags opencv` -g
LDFLAGS=`pkg-config --libs opencv`
OBJS=follower.o

all : norm

norm : $(PROG)

$(PROG) : $(OBJS) main.o
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

clean :
	rm -vf *.o

rec : clean all

.PHONY:rec clean all


