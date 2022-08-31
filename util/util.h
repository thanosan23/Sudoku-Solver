#ifndef UTIL_H
#define UTIL_H

#include "std.h"
#include "types.h"
#include "file.h"
#include "debug.h"
#include "time.h"

#define UNUSED __attribute__((unused))

#define assert(predicate, message)                                             \
        (_assert(predicate, message, __FILE__, __LINE__))

void _assert(bool predicate, const char* message,
                    const char *file, usize line) {
  if(!predicate) {
    fprintf(stdout, "%s (%s:%" PRIu64 ")\n", message, file, line);
    exit(1);
  }
}

#endif
