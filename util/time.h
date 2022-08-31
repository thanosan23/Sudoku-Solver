#ifndef TIME_H
#define TIME_H

#define NS (1e9)

#define NOW() ({                                                               \
  struct timespec t;                                                           \
  clock_gettime(CLOCK_MONOTONIC_RAW, &t);                                      \
  ((t.tv_sec * NS) + t.tv_nsec);})                                             \


#endif
