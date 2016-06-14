#ifndef CPPARENA_HEAP_ARENA_WIN32_HPP_INCLUDED
#define CPPARENA_HEAP_ARENA_WIN32_HPP_INCLUDED

#include <Windows.h>
#include <stdexcept>
#include <new>
#include <cstddef>

namespace cpparena {

  class Heap_arena {
    HANDLE heap_;

  public:
    class Error: public std::runtime_error {
    public:
      Error(const char* what_arg) :
        std::runtime_error{what_arg}
      { }
    };

    Heap_arena() :
      heap_{HeapCreate(0, 0, 0)}
    {
      if (heap_ == nullptr) {
        throw Error("Failed to allocate page / construct local heap");
      }
    }

    Heap_arena(Heap_arena&& tmp) :
      heap_{old.heap_}
    {
      old.heap_ = nullptr;
    }

    ~Heap_arena()
    {
      if (heap_ != nullptr) {
        bool success = HeapDestroy(heap_);
        if (!success) {
          throw Error("Problem destroying local heap");
        }
      }
    }

    void* allocate(std::size_t bytes)
    {
      void* result = HeapAlloc(heap_, 0, bytes);
      if (result == nullptr) {
        throw std::bad_alloc();
      }
      return result;
    }

    void deallocate(void* block, std::size_t /* bytes */)
    {
      bool success = HeapFree(heap_, 0, block);
      if (!success) {
        throw Error("Problem deallocating a local heap's block");
      }
    }
  };

}

#endif // CPPARENA_HEAP_ARENA_WIN32_HPP_INCLUDED
