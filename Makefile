CXXDIAG = -Wall -W -pedantic
CXXSTD = c++14
CXXINCLUDES = -Iinclude
CXXFLAGS = -std=$(CXXSTD) $(CXXDIAG) $(CXXINCLUDES) -O3

EXAMPLES = $(patsubst examples/%.cpp,bin/examples/%,$(wildcard examples/*.cpp))

.PHONY: all
all: $(EXAMPLES)

.PHONY: clean
clean:
	rm -rf bin obj

bin/examples/packet_example: examples/packet_example.cpp src/Heap_arena_posix.cpp -ljemalloc | bin/examples
	$(CXX) $(CXXFLAGS) -o$@ $^

bin bin/examples obj:
	mkdir $@

bin/examples: | bin
