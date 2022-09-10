#include "circular_buffer.h"
#include <errno.h>
#include <stdbool.h>

bool empty(circular_buffer_t *buffer) { return buffer->current_size == 0; }

bool full(circular_buffer_t *buffer) {
  return buffer->current_size == buffer->capacity;
}

circular_buffer_t *new_circular_buffer(size_t capacity) {
  circular_buffer_t *buffer = malloc(sizeof(circular_buffer_t));
  if (!buffer) {
    errno = ENODATA;
    exit(EXIT_FAILURE);
  }
  buffer->head = 0;
  buffer->tail = 0;
  buffer->current_size = 0;
  buffer->capacity = capacity;
  buffer->values = malloc(capacity * sizeof(buffer_value_t));
  if (!buffer->values) {
    errno = ENODATA;
    exit(EXIT_FAILURE);
  }
  return buffer;
}

int16_t write(circular_buffer_t *buffer, buffer_value_t value) {
  if (full(buffer))
    exit(EXIT_FAILURE);
  if (buffer->tail == buffer->capacity - 1)
    buffer->tail = 0;
  buffer->values[buffer->tail++] = value;
  buffer->current_size++;
  return EXIT_SUCCESS;
}

int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value) {
  buffer->values[buffer->head] = value;
  return EXIT_SUCCESS;
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *value) {
  if (empty(buffer)) {
    errno = ENODATA;
    return EXIT_FAILURE;
  }
  *value = buffer->values[buffer->head];
  buffer->head++;
  return EXIT_SUCCESS;
}

void delete_buffer(circular_buffer_t *buffer) { free(buffer); }

void clear_buffer(circular_buffer_t *buffer) {
  buffer->head = 0;
  buffer->tail = 1;
}
