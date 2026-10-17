#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer) {
  RUN_TEST_CASE(CircularBuffer, CorrectSizeConstructed);
  RUN_TEST_CASE(CircularBuffer, ErrorOnEmptyBufferTake);
  RUN_TEST_CASE(CircularBuffer, TakeGivesTheSameValueAsPut);
  RUN_TEST_CASE(CircularBuffer, CreatedWithAvailableSpaceEqualToSize);
  RUN_TEST_CASE(CircularBuffer, NotNullConstructed);
  RUN_TEST_CASE(CircularBuffer, PutDecrementsAvailableSpace);
  RUN_TEST_CASE(CircularBuffer, TakeIncrementsAvailableSpace);
  RUN_TEST_CASE(CircularBuffer, FirstInFirstOut);
  RUN_TEST_CASE(CircularBuffer, TakeWithNullItemPtrReturnsError);
  RUN_TEST_CASE(CircularBuffer, FreeOfBufferMakesThePointerToItNull);
  RUN_TEST_CASE(CircularBuffer, PutReturnsAvailableSpaceOnNotError);
  RUN_TEST_CASE(CircularBuffer, TakeReturnsAvailableSpaceOnNotError);
  RUN_TEST_CASE(CircularBuffer, InvalidSizeInConstructorReturnsNULL);
  RUN_TEST_CASE(CircularBuffer, AddMoreThanSizeElemsKeepsAvailableSpaceZero);
  RUN_TEST_CASE(CircularBuffer, AddMoreThanSizeElementsRemovesOldOnes);
  RUN_TEST_CASE(CircularBuffer, TestBufferWithSize1);
  RUN_TEST_CASE(CircularBuffer, NullBufPtr);
  RUN_TEST_CASE(CircularBuffer, UseAfterFreeBuf);
  RUN_TEST_CASE(CircularBuffer, ManySpins);
}
