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
	queue<int> ref_queue;
	QueueFixed<int> queue(20);

	int max_api_calls = 20;
	int api_calls = 0;
	while (api_calls < max_api_calls) {
		int rand_api = random(0, 2);
		// enqueue
		if (rand_api == 0) {
			int rand_val = random(0, 20);
			ref_queue.push(rand_val);
			queue.enqueue(rand_val);
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

		//printf("%d) queue size = %d\n", api_calls, queue.size());
		ASSERT_EQ(ref_queue.size(), queue.size());

		++api_calls;
	}
}

TEST(queue, randomapi) {
	queue<int> ref_queue;
	Queue<int> queue;

	int max_api_calls = 10000;
	int api_calls = 0;
	while (api_calls < max_api_calls) {
		int rand_api = random(0, 2);
		// enqueue
		if (rand_api == 0) {
			int rand_val = random(0, 20);
			ref_queue.push(rand_val);
			queue.enqueue(rand_val);
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

		//printf("%d) queue size = %d\n", api_calls, queue.size());
		ASSERT_EQ(ref_queue.size(), queue.size());

		++api_calls;
	}
}

TEST(queuelist, randomapi) {
	queue<int> ref_queue;
	QueueList<int> queue;

	int max_api_calls = 1000;
	int api_calls = 0;
	while (api_calls < max_api_calls) {
		int rand_api = random(0, 2);
		// enqueue
		if (rand_api == 0) {
			int rand_val = random(0, 20);
			ref_queue.push(rand_val);
			queue.enqueue(rand_val);
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

		//printf("%d) queue size = %d\n", api_calls, queue.size());
		ASSERT_EQ(ref_queue.size(), queue.size());

		++api_calls;
	}
}

int main(int argc, char **argv)
{
	srand(time(0));
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
