#include "circular_buffer.h"
#include <stdlib.h>

CircularBuffer create_circular_buffer(size_t size) {
  (void)size;
  return (CircularBuffer)0x1;
}

void delete_circular_buffer(CircularBuffer *buf) { (void)buf; }

size_t circular_buffer_size(CircularBuffer *buf) {
  (void)buf;
  return 10;
}

size_t circular_buffer_available(CircularBuffer *buf) {
  (void)buf;
  return 10;
}

ssize_t circular_buffer_get(CircularBuffer *buf, CircularBufferItem *item) {
  (void)buf;
  (void)item;
  *item = 100;
  return -1;
}

void circular_buffer_put(CircularBuffer *buf, CircularBufferItem value) {
  (void)buf;
  (void)value;
}
