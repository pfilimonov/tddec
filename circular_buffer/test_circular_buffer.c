#include "circular_buffer.h"
#include "unity_fixture.h"

TEST_GROUP(CircularBuffer);

static CircularBuffer buf;

TEST_SETUP(CircularBuffer) { buf = create_circular_buffer(10); }
TEST_TEAR_DOWN(CircularBuffer) { delete_circular_buffer(&buf); }

TEST(CircularBuffer, NotNullConstructed) {
  TEST_ASSERT_NOT_EQUAL_PTR(NULL, buf);
}

TEST(CircularBuffer, CorrectSizeConstructed) {
  TEST_ASSERT_EQUAL_INT(10, circular_buffer_size(&buf));
}

TEST(CircularBuffer, CreatedWithAvailableSpaceEqualToSize) {
  TEST_ASSERT_EQUAL_INT(circular_buffer_size(&buf),
                        circular_buffer_available(&buf));
}

TEST(CircularBuffer, ErrorOnEmptyBufferGet) {
  CircularBufferItem value;
  TEST_ASSERT_EQUAL_INT(-1, circular_buffer_get(&buf, &value));
}

TEST(CircularBuffer, GetGivesTheSameValueAsPut) {
  circular_buffer_put(&buf, 100);
  CircularBufferItem value_to_get = 99;
  circular_buffer_get(&buf, &value_to_get);
  TEST_ASSERT_EQUAL_INT(100, value_to_get);
}
