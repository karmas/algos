#include <queue>
#include "gtest/gtest.h"
#include "queue.h"

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

TEST(queuefixed, randomapi) {
	srand(time(0));
	queue<int> ref_queue;
	QueueFixed<int> queue(10);

	int max_api_calls = 10;
	int api_calls = 0;
	while (api_calls < max_api_calls) {
		int rand_api = random(0, 2);
		// enqueue
		if (rand_api == 0) {
			int rand_val = random(0, 20);
			ref_queue.push(rand_val);
		}
		// dequeue
		else {
			if (ref_queue.empty()) {
				ASSERT_TRUE(queue.isEmpty());
				continue;
			}

			int ref_val = ref_queue.front();
			ref_queue.pop();
			int val = queue.dequeue();
			ASSERT_EQ(ref_val, val);
		}

		++api_calls;
	}
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
