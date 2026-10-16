#include <stdlib.h>

typedef struct CircularBufferStruct *CircularBuffer;
typedef int CircularBufferItem;

CircularBuffer create_circular_buffer(size_t size);
void delete_circular_buffer(CircularBuffer *buf);
size_t circular_buffer_size(CircularBuffer *buf);
size_t circular_buffer_available(CircularBuffer *buf);
ssize_t circular_buffer_get(
    CircularBuffer *buf,
    CircularBufferItem
        *item); // returns remaining available space on success, -1 on error
void circular_buffer_put(CircularBuffer *buf, CircularBufferItem value);
