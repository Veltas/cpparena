#ifndef CPPARENA_HEAP_ARENA_HPP_INCLUDED
#define CPPARENA_HEAP_ARENA_HPP_INCLUDED

#if defined(_WIN32)
  #include <Heap_arena_win32.hpp>
#elif defined(__unix__)
  #include <Heap_arena_posix.hpp>
#elif
  #error "Platform headers missing"
#endif

#endif // CPPARENA_HEAP_ARENA_HPP_INCLUDED
