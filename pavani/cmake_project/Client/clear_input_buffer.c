#include "clear_input_buffer.h"

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

