#include <CppUTest/TestHarness.h>
#include <malloc.h>
#include <stdlib.h>

TEST_GROUP(sprintf) {
  char *output;
  const char *expected;
  void setup() { expected = ""; }
  void teardown() {}
  void expect(const char *s) {
    size_t size = strlen(s) + 2;
    output = (char *)malloc(sizeof(char) * size);
    CHECK(output != NULL);
    memset(output, 0xaa, size + 1);
    expected = s;
  }
  void given(int charsWritten) {
    LONGS_EQUAL(strlen(expected), charsWritten);
    STRCMP_EQUAL(expected, output);
    BYTES_EQUAL(0xaa, output[strlen(expected) + 1]);
    free(output);
  }
};

TEST(sprintf, NoFormatOperations) {
  expect("hey");
  given(sprintf(output, "hey"));
}

TEST(sprintf, InsertString) {
  expect("Hello World\n");
  given(sprintf(output, "Hello %s\n", "World"));
}

TEST(sprintf, InsertInt) {
  expect("int=1");
  given(sprintf(output, "int=%d", 1));
}

TEST(sprintf, InsertIntAndString) {
  expect("int=1,str=hey");
  given(sprintf(output, "int=%d,str=%s", 1, "hey"));
}

TEST(sprintf, LongString) {
  char *long_string = (char *)malloc(sizeof(char) * 10000);
  long_string[10000 - 1] = '\0';
  long_string[0] = 'h';
  long_string[1] = 'e';
  long_string[2] = 'y';
  expect(long_string);
  given(sprintf(output, long_string));
}

TEST(sprintf, InsertPtr) {
  expect("ptr=0xffffffffffffffff");
  given(sprintf(output, "ptr=%p", (void *)-1));
}
