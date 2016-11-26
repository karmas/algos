#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

struct Bsearch {
	/**
	 * @param arr sorted list of numbers
	 * @return index if key found else -1
	 */
	static int rank(const vector<int> &arr, int key) {
		int lo =  0;
		int hi = arr.size();
		while (lo < hi) {
			int mid = lo + ((hi - lo) / 2);
			if (arr[mid] == key) {
				return mid;
			}
			else if (arr[mid] < key) {
				lo = mid + 1;
			}
			else {
				hi = mid;
			}
		}
		return -1;
	}
};

int main(int argc, const char *argv[])
{
	assert(argc > 1);
	ifstream ifs(argv[1]);
	string line;
	vector<int> whitelist;
	while (getline(ifs, line)) {
		whitelist.push_back(stoi(line));
	}
	sort(whitelist.begin(), whitelist.end());

	int key = 0;
	while (cin >> key) {
		int test_find = Bsearch::rank(whitelist, key);
#ifdef DEBUG
		vector<int>::const_iterator ref_find_it = find(whitelist.begin(), whitelist.end(), key);
		if (ref_find_it == whitelist.end() && test_find != -1) {
			printf("key=%d\n", key);
			assert(false);
		}
		else if (ref_find_it != whitelist.end() && test_find == -1) {
			printf("key=%d\n", key);
			assert(false);
		}
#endif
		if (test_find == -1) {
			cout << key << endl;
		}
	}

	return 0;
}
