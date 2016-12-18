#include <cstdlib>
#include "gtest/gtest.h"
#include "sort.h"

using namespace std;

/**
 * @return random number in range [from, to)
 */
int random(int from, int to)
{
	assert(to > from);
	int r = rand();
	int range = to - from;
	int inrange = r % range;
	int val = from + inrange;
	assert(val >= from);
	assert(val < to);
	return val;
}

/**
 * @return allocated random array of size n
 */
int *randomArray(int n)
{
	assert(n > 0);
	int *arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = random(-100, 100);
	}
	return arr;
}

// print [i, j)
template<typename T>
void printArray(const T *arr, int i, int j)
{
	const char sep = ',';
	for (int k = i; k < j; ++k) {
		if (k > i) printf("%c", sep);
		printf("%d", arr[k]);
	}
	printf("\n");
}

bool debug = false;

TEST ( selection, verify )
{
	int samples = 30;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		selection(arr, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( insertionExch, verify )
{
	int samples = 10;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		insertionExch(arr, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( insertion, verify )
{
	int samples = 30;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		insertion(arr, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( shell, verify )
{
	int samples = 30;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		shell(arr, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( merge, verify )
{
	int samples = 30;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		merge(arr, 0, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( mergeBU, verify )
{
	int samples = 30;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		mergeBU(arr, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( quick, verify )
{
	int samples = 30;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		quick(arr, 0, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( quick2, verify )
{
	int samples = 30;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		quick2(arr, 0, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( quick3way, verify )
{
	int samples = 30;
	for (int i = 0; i < samples; i++) {
		int n = random(1, 100);
		int *arr = randomArray(n);
		if (debug) {
			printf("\tsample=%d size=%d\n", i, n);
			printArray(arr, 0, n);
		}
		quick3way(arr, 0, n);
		if (debug) {
			printf("\tsorted\n");
			printArray(arr, 0, n);
		}
		ASSERT_TRUE(isSorted(arr, n));
		ASSERT_TRUE(isSortedRecursive(arr, 0, n));
		delete[] arr;
	}
}

TEST ( heap, verify )
{
    int samples = 30;
    for (int i = 0; i < samples; i++) {
        int n = random(1, 100);
        int *arr = randomArray(n);
        if (debug) {
            printf("\tsample=%d size=%d\n", i, n);
            printArray(arr, 0, n);
        }
        heap(arr, n);
        if (debug) {
            printf("\tsorted\n");
            printArray(arr, 0, n);
        }
        ASSERT_TRUE(isSorted(arr, n));
        ASSERT_TRUE(isSortedRecursive(arr, 0, n));
        delete[] arr;
    }
}

int main(int argc, char **argv)
{
	srand(time(0));
	::testing::InitGoogleTest(&argc, argv);
	if (argc > 1) {
		debug = true;
	}
	return RUN_ALL_TESTS();
}
