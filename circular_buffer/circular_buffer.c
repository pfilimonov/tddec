#include "circular_buffer.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *storage;
  size_t size;
  size_t read_idx;
  size_t write_idx;
  size_t available;
} CircularBufferStruct;

static CircularBufferStruct *convert(CircularBuffer *buf) {
  return (CircularBufferStruct *)(*buf);
}

static bool is_empty(CircularBuffer *buf) {
  CircularBufferStruct *cb = convert(buf);
  return cb->read_idx == cb->write_idx;
}

static bool invalid_buffer(CircularBuffer *buf) {
  return buf == NULL || *buf == NULL;
}

CircularBuffer create_circular_buffer(size_t size) {
  if (size == 0) {
    return NULL;
  }
  CircularBufferStruct *buf = malloc(sizeof(CircularBufferStruct));
  if (buf == NULL) {
    return NULL;
  }
  buf->storage = malloc(sizeof(int) * size);
  if (buf->storage == NULL) {
    return NULL;
  }
  buf->write_idx = 0;
  buf->read_idx = 0;
  buf->size = size;
  buf->available = 0;
  return (CircularBuffer)buf;
}

void free_circular_buffer(CircularBuffer *buf) {
  if (invalid_buffer(buf)) {
    return;
  }
  CircularBufferStruct *cb = convert(buf);
  free(cb->storage);
  free(cb);
  *buf = NULL;
}

ssize_t circular_buffer_size(CircularBuffer *buf) {
  if (invalid_buffer(buf)) {
    return -1;
  }
  return (ssize_t)convert(buf)->size;
}

ssize_t circular_buffer_available(CircularBuffer *buf) {
  if (invalid_buffer(buf)) {
    return -1;
  }
  CircularBufferStruct *cb = convert(buf);
  size_t diff = cb->write_idx - cb->read_idx;
  if (diff > cb->size) {
    return 0;
  }
  return (ssize_t)(cb->size - diff);
}

ssize_t circular_buffer_take(CircularBuffer *buf, CircularBufferItem *item) {
  if (item == NULL || invalid_buffer(buf)) {
    return -1;
  }
  CircularBufferStruct *cb = convert(buf);
  if (is_empty(buf)) {
    return -1;
  }
  *item = cb->storage[cb->read_idx % cb->size];
  cb->read_idx = (cb->read_idx + 1);
  return (ssize_t)circular_buffer_available(buf);
}

ssize_t circular_buffer_put(CircularBuffer *buf, CircularBufferItem value) {
  if (invalid_buffer(buf)) {
    return -1;
  }
  CircularBufferStruct *cb = convert(buf);
  if (!is_empty(buf) &&
      cb->write_idx % cb->size ==
          cb->read_idx % cb->size) { // about to hit the read ptr
    cb->read_idx = (cb->read_idx + 1);
  }
  cb->storage[cb->write_idx % cb->size] = value;
  cb->write_idx = (cb->write_idx + 1);

  return circular_buffer_available(buf);
}
