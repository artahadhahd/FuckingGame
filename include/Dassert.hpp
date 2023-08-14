#ifndef DASSERT
#include <cstdlib>
#include <iostream>

#include "Types.hpp"

static inline void dassertionError(bool const condition, i32 line,
                                   std::string file) {
  if (!condition) {
    std::cerr << "Dassert error in " << file << " on line " << line << '\n';
    exit(2);
  }
}

#define DASSERT(cond) dassertionError(cond, __LINE__, __FILE__)
#endif
