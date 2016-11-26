#include <stack>
#include "gtest/gtest.h"
#include "stack.h"

using namespace std;

/**
 * @return random number in range [from, to)
 */
int random(int from, int to)
{
	int r = rand();
	int range = to - from;
	int inrange = r % range;
	return from + inrange;
}

TEST(stack, randomapi) {
	stack<int> ref_stack;
	StackList<int> stack;

	int max_api_calls = 1000;
	int api_calls = 0;
	while (api_calls < max_api_calls) {
		int rand_api = random(0, 2);
		if (rand_api == 0) {
			int rand_val = random(0, 20);
			ref_stack.push(rand_val);
			stack.push(rand_val);
		}
		else {
			if (ref_stack.empty()) {
				ASSERT_TRUE(stack.isEmpty());
				continue;
			}

			int ref_val = ref_stack.top();
			ref_stack.pop();
			int val = stack.pop();
			ASSERT_EQ(ref_val, val);
		}

		//printf("%d) stack size = %d\n", api_calls, stack.size());
		ASSERT_EQ(ref_stack.size(), stack.size());
		++api_calls;
	}
}

int main(int argc, char **argv)
{
	srand(time(0));
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
