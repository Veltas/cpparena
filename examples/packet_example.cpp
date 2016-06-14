#include <Arena_allocator.hpp>
#include <Heap_arena.hpp>
#include <queue>
#include <list>
#include <iostream>

using namespace cpparena;

class Packet {
public:
  Packet(const char* init) : pfft{init}
  { }
  std::string pfft;
};

template <class T, class A = std::allocator<T> >
using Fixed_allocs_queue = std::queue<T, std::list<T, A> >;

int main()
{
  // Create extra heap arena
  Heap_arena packet_arena;

  // Allocator to use this arena
  using Packet_allocator = Arena_allocator<Packet>;
  Packet_allocator allocator{packet_arena};

  // This queue will do fixed-size allocations from our arena
  using Packet_queue = Fixed_allocs_queue<Packet, Packet_allocator>;
  Packet_queue packet_queue{std::list<Packet, Packet_allocator>{allocator}};

  // Quick demonstration of using the queue

  packet_queue.emplace("hello there");
  packet_queue.emplace("what's up");
  packet_queue.emplace("good times");
  packet_queue.emplace("we're having");
  packet_queue.emplace("and such");

  while (not packet_queue.empty()) {
    std::cout << packet_queue.front().pfft << std::endl;
    packet_queue.pop();
  }
}
