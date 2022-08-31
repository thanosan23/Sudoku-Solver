#ifndef FILE_H
#define FILE_H

u8 *read_file(FILE *file) {
  u8 *buffer = malloc(1024);
  i32 cur = getc(file);
  i32 i = 0;
  while(cur != EOF) {
    buffer[i++] = cur;
    cur = getc(file);
  };
  return buffer;
}

#endif
