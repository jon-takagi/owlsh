CXX=gcc
CXXFLAGS=-Wall -Wextra -Werror -fast -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all: owlsh

owlsh: owlsh.o
	$(CXX) $(LDFLAGS) -o $@ $^

clang: owlsh.o
	clang $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o owlsh

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./owlsh
