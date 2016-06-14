#ifndef CPPARENA_ARENA_ALLOCATOR_HPP_INCLUDED
#define CPPARENA_ARENA_ALLOCATOR_HPP_INCLUDED

#include <Heap_arena.hpp>
#include <cstddef>

namespace cpparena {

  template <class T>
  class Arena_allocator {
    Heap_arena* arena_;

  public:
    using value_type = T;

    template <class U>
    class rebind {
    public:
      using other = Arena_allocator<U>;
    };

    Arena_allocator(Heap_arena& arena) :
      arena_{&arena}
    { }

    template <class U>
    Arena_allocator(const Arena_allocator<U>& other) :
      arena_{&other.this_arena()}
    { }

    value_type* allocate(std::size_t n) const
    {
      return (value_type*)arena_->allocate(n * sizeof (value_type));
    }

    void deallocate(value_type* obj, std::size_t n) const
    {
      arena_->deallocate(obj, n * sizeof (value_type));
    }

    template <class U>
    bool operator == (const cpparena::Arena_allocator<U>& other) const
    {
      return arena_ == &other.this_arena;
    }

    template <class U>
    bool operator != (const cpparena::Arena_allocator<U>& other) const
    {
      return arena_ != &other.this_arena;
    }

    Heap_arena& this_arena() const
    {
      return *arena_;
    }
  };

}

#endif // CPPARENA_ARENA_ALLOCATOR_HPP_INCLUDED
