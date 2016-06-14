#include <Heap_arena_posix.hpp>

extern "C" {
  #include <jemalloc/jemalloc.h>
}

#include <cassert>
#include <new>

namespace {

  inline unsigned arena_alloc()
  {
    unsigned arena;
    std::size_t arena_byte_size = sizeof (arena);

    // Extend number of arenas
    if (mallctl(
      "arenas.extend",
      (void*)&arena,
      &arena_byte_size,
      nullptr,
      0))
    {
      throw cpparena::Heap_arena::Error("Failed to get new arena");
    }

    return arena;
  }

  inline void arena_free(unsigned /* arena */)
  {
    // TODO
  }

}

cpparena::Heap_arena::Heap_arena() :
  arena_{arena_alloc()}
{ }

cpparena::Heap_arena::Heap_arena(Heap_arena&& tmp) :
  arena_{tmp.arena_}
{
  tmp.is_active_ = false;
}

cpparena::Heap_arena::~Heap_arena()
{
  if (is_active_) arena_free(arena_);
}

void* cpparena::Heap_arena::allocate(std::size_t bytes)
{
  void* result = mallocx(bytes, MALLOCX_ARENA(arena_));
  if (result == nullptr) {
    throw std::bad_alloc();
  }
  return result;
}

void cpparena::Heap_arena::deallocate(void* block, std::size_t bytes)
{
  sdallocx(block, bytes, MALLOCX_ARENA(arena_));
}
