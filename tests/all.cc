#include "map_tests.h"
#include "queue_test.h"
#include "set_test.h"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
