#include "gtest/gtest.h"

using namespace std;

bool debug = false;
const int calls = 1000;

TEST( graph, basic )
{
}

int main(int argc, char **argv)
{
  srand(time(0));
  if (argc > 1) {
    debug = true;
  }
  printf("debug mode = %d\n", debug);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
