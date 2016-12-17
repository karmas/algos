#include <cstdlib>
#include "gtest/gtest.h"
#include "pq.h"

using namespace std;

namespace {
	vector<int> tiny;
	vector<int> top5;
}

void init()
{
	tiny.push_back(644);
	tiny.push_back(4121);
	tiny.push_back(2678);
	tiny.push_back(4409);
	tiny.push_back(837);
	tiny.push_back(3229);
	tiny.push_back(4732);
	tiny.push_back(4381);
	tiny.push_back(66);
	tiny.push_back(4747);
	tiny.push_back(2156);
	tiny.push_back(1025);
	tiny.push_back(2520);
	tiny.push_back(708);
	tiny.push_back(3532);
	tiny.push_back(4050);

	top5.push_back(4747);
	top5.push_back(4732);
	top5.push_back(4409);
	top5.push_back(4381);
	top5.push_back(4121);
}

TEST ( pq, unordered_array )
{
	const int topm = 5;
	MinPQ_unordered_array<int> pq(topm);
	for (vector<int>::const_iterator tit = tiny.begin(); tit != tiny.end(); ++tit) {
		int val = *tit;
		if (pq.size() < topm) {
			pq.insert(val);
		}
		else {
			int min = pq.min();
			if (val > min) {
				pq.delMin();
				pq.insert(val);
			}
		}
	}

	vector<int> res(topm);
	for (int i = topm - 1; i >= 0; --i) {
		res[i] = pq.delMin();
	}
	ASSERT_EQ(top5, res);
}

TEST ( pq, ordered_array )
{
	const int topm = 5;
	MinPQ_ordered_array<int> pq(topm + 1);
	for (vector<int>::const_iterator tit = tiny.begin(); tit != tiny.end(); ++tit) {
		pq.insert(*tit);
		if (pq.size() > topm) {
			pq.delMin();
		}
	}

	vector<int> res(topm);
	for (int i = topm - 1; i >= 0; --i) {
		res[i] = pq.delMin();
	}
	ASSERT_EQ(top5, res);
}

TEST ( pq, unordered_list )
{
	const int topm = 5;
	MinPQ_unordered_list<int> pq;
	for (vector<int>::const_iterator tit = tiny.begin(); tit != tiny.end(); ++tit) {
		pq.insert(*tit);
		if (pq.size() > topm) {
			pq.delMin();
		}
	}

	vector<int> res(topm);
	for (int i = topm - 1; i >= 0; --i) {
		res[i] = pq.delMin();
	}
	ASSERT_EQ(top5, res);
}

TEST ( pq, ordered_list )
{
	const int topm = 5;
	MinPQ_ordered_list<int> pq;
	for (vector<int>::const_iterator tit = tiny.begin(); tit != tiny.end(); ++tit) {
		pq.insert(*tit);
		if (pq.size() > topm) {
			pq.delMin();
		}
	}

	vector<int> res(topm);
	for (int i = topm - 1; i >= 0; --i) {
		res[i] = pq.delMin();
	}
	ASSERT_EQ(top5, res);
}

TEST ( pq, heap )
{
	const int topm = 5;
	MinPQ<int> pq(topm + 1);
	for (vector<int>::const_iterator tit = tiny.begin(); tit != tiny.end(); ++tit) {
		pq.insert(*tit);
		if (pq.size() > topm) {
			pq.delMin();
		}
	}

	vector<int> res(topm);
	for (int i = topm - 1; i >= 0; --i) {
		res[i] = pq.delMin();
	}
	ASSERT_EQ(top5, res);
}

int main(int argc, char **argv)
{
	init();
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
