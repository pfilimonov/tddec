#include "circular_buffer.h"
#include "unity_fixture.h"
#include <limits.h>

TEST_GROUP(CircularBuffer);

static CircularBuffer buf;

TEST_SETUP(CircularBuffer) { buf = create_circular_buffer(3); }
TEST_TEAR_DOWN(CircularBuffer) {
  if (buf != NULL) {
    free_circular_buffer(&buf);
  }
}

TEST(CircularBuffer, NotNullConstructed) {
  TEST_ASSERT_NOT_EQUAL_PTR(NULL, buf);
}

TEST(CircularBuffer, CorrectSizeConstructed) {
  TEST_ASSERT_EQUAL_INT(3, circular_buffer_size(&buf));
}

TEST(CircularBuffer, CreatedWithAvailableSpaceEqualToSize) {
  TEST_ASSERT_EQUAL_INT(circular_buffer_size(&buf),
                        circular_buffer_available(&buf));
}

TEST(CircularBuffer, ErrorOnEmptyBufferTake) {
  CircularBufferItem value;
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_take(&buf, &value));
}

TEST(CircularBuffer, TakeGivesTheSameValueAsPut) {
  circular_buffer_put(&buf, 100);
  CircularBufferItem value_to_get = 99;
  circular_buffer_take(&buf, &value_to_get);
  TEST_ASSERT_EQUAL_INT(100, value_to_get);
}

TEST(CircularBuffer, PutDecrementsAvailableSpace) {
  circular_buffer_put(&buf, 100);
  TEST_ASSERT_EQUAL_INT(2, circular_buffer_available(&buf));
}

TEST(CircularBuffer, TakeIncrementsAvailableSpace) {
  circular_buffer_put(&buf, 100);
  CircularBufferItem val;
  circular_buffer_take(&buf, &val);
  TEST_ASSERT_EQUAL_INT(3, circular_buffer_available(&buf));
}

TEST(CircularBuffer, FirstInFirstOut) {
  circular_buffer_put(&buf, 100);
  circular_buffer_put(&buf, 99);
  CircularBufferItem value_to_get;
  circular_buffer_take(&buf, &value_to_get);
  TEST_ASSERT_EQUAL_INT(100, value_to_get);
  circular_buffer_take(&buf, &value_to_get);
  TEST_ASSERT_EQUAL_INT(99, value_to_get);
}

TEST(CircularBuffer, TakeWithNullItemPtrReturnsError) {
  circular_buffer_put(&buf, 100); // make buffer not empty
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_take(&buf, NULL));
}

TEST(CircularBuffer, FreeOfBufferMakesThePointerToItNull) {
  TEST_ASSERT_NOT_EQUAL_PTR(NULL, buf);
  free_circular_buffer(&buf);
  TEST_ASSERT_EQUAL_PTR(NULL, buf);
}

TEST(CircularBuffer, PutReturnsAvailableSpaceOnNotError) {
  TEST_ASSERT_EQUAL_INT(2, circular_buffer_put(&buf, 100));
}

TEST(CircularBuffer, TakeReturnsAvailableSpaceOnNotError) {
  circular_buffer_put(&buf, 100);
  circular_buffer_put(&buf, 99);
  CircularBufferItem val;
  TEST_ASSERT_EQUAL_INT(2, circular_buffer_take(&buf, &val));
}

TEST(CircularBuffer, InvalidSizeInConstructorReturnsNULL) {
  TEST_ASSERT_EQUAL_PTR(NULL, create_circular_buffer(0));
}

TEST(CircularBuffer, AddMoreThanSizeElemsKeepsAvailableSpaceZero) {
  circular_buffer_put(&buf, 100);
  circular_buffer_put(&buf, 99);
  circular_buffer_put(&buf, 98);
  TEST_ASSERT_EQUAL_INT(0, circular_buffer_available(&buf));
  circular_buffer_put(&buf, 97);
  TEST_ASSERT_EQUAL_INT(0, circular_buffer_available(&buf));
}

TEST(CircularBuffer, AddMoreThanSizeElementsRemovesOldOnes) {
  circular_buffer_put(&buf, 100);
  circular_buffer_put(&buf, 99);
  circular_buffer_put(&buf, 98);
  circular_buffer_put(&buf, 97);
  CircularBufferItem val;
  circular_buffer_take(&buf, &val);
  TEST_ASSERT_EQUAL_INT(99, val);
  circular_buffer_take(&buf, &val);
  TEST_ASSERT_EQUAL_INT(98, val);
  circular_buffer_take(&buf, &val);
  TEST_ASSERT_EQUAL_INT(97, val);
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_take(&buf, &val));
}

TEST(CircularBuffer, TestBufferWithSize1) {
  CircularBuffer buf1 = create_circular_buffer(1);
  circular_buffer_put(&buf1, 100);
  circular_buffer_put(&buf1, 99);
  CircularBufferItem val;
  circular_buffer_take(&buf1, &val);
  TEST_ASSERT_EQUAL_INT(99, val);
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_take(&buf1, &val));
  free_circular_buffer(&buf1);
}

TEST(CircularBuffer, NullBufPtr) {
  // no seg fault
  free_circular_buffer(NULL);
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_size(NULL));
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_available(NULL));
  CircularBufferItem val;
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_take(NULL, &val));
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_put(NULL, 0));
}

TEST(CircularBuffer, UseAfterFreeBuf) {
  // no seg fault
  free_circular_buffer(&buf);
  free_circular_buffer(&buf); // double free
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_size(&buf));
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_available(&buf));
  CircularBufferItem val;
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_take(&buf, &val));
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_put(&buf, 0));
}

TEST(CircularBuffer, ManySpins) {
  CircularBufferItem val;

  for (int i = 0; i < 5; i++) {
    circular_buffer_put(&buf, 100);
    circular_buffer_put(&buf, 99);

    circular_buffer_take(&buf, &val);
    TEST_ASSERT_EQUAL_INT(100, val);

    circular_buffer_take(&buf, &val);
    TEST_ASSERT_EQUAL_INT(99, val);
  }

  circular_buffer_put(&buf, 97);
  circular_buffer_take(&buf, &val);
  TEST_ASSERT_EQUAL_INT(97, val);
}
