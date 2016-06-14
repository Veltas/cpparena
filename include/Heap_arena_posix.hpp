#ifndef CPPARENA_HEAP_ARENA_POSIX_HPP_INCLUDED
#define CPPARENA_HEAP_ARENA_POSIX_HPP_INCLUDED

#include <stdexcept>
#include <cstddef>

namespace cpparena {

  class Heap_arena {
    unsigned arena_;
    bool is_active_ = true;

  public:
    class Error: public std::runtime_error {
    public:
      Error(const char* what_arg) :
        std::runtime_error{what_arg}
      { }
    };

    Heap_arena();

    Heap_arena(Heap_arena&& tmp);

    ~Heap_arena();

    void* allocate(std::size_t bytes);

    void deallocate(void* block, std::size_t bytes);
  };

}

#endif // CPPARENA_HEAP_ARENA_POSIX_HPP_INCLUDED
