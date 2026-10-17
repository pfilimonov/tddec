#include <stdlib.h>

typedef struct CircularBufferStruct *CircularBuffer;
typedef int CircularBufferItem;

CircularBuffer create_circular_buffer(size_t size);
void free_circular_buffer(CircularBuffer *buf);
ssize_t circular_buffer_size(CircularBuffer *buf);
ssize_t circular_buffer_available(CircularBuffer *buf);
ssize_t circular_buffer_take(
    CircularBuffer *buf,
    CircularBufferItem
        *item); // returns remaining available space on success, -1 on error
ssize_t circular_buffer_put(CircularBuffer *buf, CircularBufferItem value);
