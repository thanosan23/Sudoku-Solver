#ifndef DEBUG_H
#define DEBUG_H

#define LOG(fmt, ...)                                                          \
  fprintf(stderr, "[%s:%d][%s] " fmt "\n", __FILE__, __LINE__,                 \
      __func__, __VA_ARGS__);

#endif
