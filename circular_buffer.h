#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdlib.h>

typedef uint8_t buffer_value_t;

typedef struct circular_buffer
{
  buffer_value_t *values;
  size_t head;
  size_t tail;
  size_t capacity;
  size_t current_size;
} circular_buffer_t;

int16_t write(circular_buffer_t *, buffer_value_t);
int16_t overwrite(circular_buffer_t *, buffer_value_t);
int16_t read(circular_buffer_t *, buffer_value_t *);
circular_buffer_t *new_circular_buffer(size_t capacity);
void delete_buffer(circular_buffer_t *buffer);
void clear_buffer(circular_buffer_t *buffer);

#endif // CIRCULAR_BUFFER_H
