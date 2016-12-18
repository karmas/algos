#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <cassert>

template <typename T>
bool isSorted(const T *arr, int n)
{
	for (int i = 0; i < n - 1; ++i) {
		if (arr[i] > arr[i+1]) {
			return false;
		}
	}
	return true;
}

/**
 * @return true if [i, j) sorted
 */
template <typename T>
bool isSortedRecursive(const T *arr, int i, int j)
{
	if (j - i <= 1) {
		return true;
	}

	return (arr[i] <= arr[i+1]) && isSortedRecursive(arr, i + 1, j);
}

template <typename T>
void exch(T *arr, int i, int j)
{
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template <typename T>
void selection(T *arr, int n)
{
	// [0, i) smallest in sorted order
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		exch(arr, i, min);
	}
}

template <typename T>
void insertionExch(T *arr, int n)
{
	// [0, i) in sorted order
	for (int i = 1; i < n; i++) {
		int j = i;
		while (j > 0 && arr[j] < arr[j-1]) {
			exch(arr, j, j-1);
			--j;
		}
	}
}

template <typename T>
void insertion(T *arr, int n)
{
	// [0, i) in sorted order
	for (int i = 1; i < n; i++) {
		T key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j+1] = arr[j];
			--j;
		}
		arr[j+1] = key;
	}
}

template <typename T>
void shell(T *arr, int n)
{
	int h = 1;
	while (h < n/3) h = 3*h + 1;
	while (h > 0) {
		for (int i = h; i < n; ++i) {
			int j = i;
			while (j >= h && arr[j] < arr[j-h]) {
				exch(arr, j, j-h);
				j -= h;
			}
		}
		h = h/3;
	}
}

template<typename T>
void doMerge(T *arr, int s, int m, int e)
{
	// now merge the 2 sorted sub arrays
	int ln = m - s;
	T la[ln];
	memcpy(la, arr + s, sizeof(T) * ln);

	int rn = e - m;
	T ra[rn];
	memcpy(ra, arr + m, sizeof(T) * rn);

	int l = 0;
	int r = 0;
	// [s, i) sorted
	for (int i = s; i < e; ++i) {
		if (l >= ln) {
			arr[i] = ra[r++];
		}
		else if (r >= rn) {
			arr[i] = la[l++];
		}
		else if (la[l] < ra[r]) {
			arr[i] = la[l++];
		}
		else {
			arr[i] = ra[r++];
		}
	}
}

// sort [s, e)
template <typename T>
void merge(T *arr, int s, int e)
{
	int n = e - s;
	if (n <= 1) {
		return;
	}
	int m = s + n/2;
	merge(arr, s, m);
	merge(arr, m, e);
	doMerge(arr, s, m, e);
}

template <typename T>
void mergeBU(T *arr, int n)
{
	// size of subarrays to merge
	for (int sz = 1; sz < n; sz *= 2) {
		// run through all subarrays
		for (int s = 0; s < n - sz; s += 2 * sz) {
			int m = s + sz;
			assert(m <= n);
			int e = std::min(m + sz, n);
			assert(e <= n);
			doMerge(arr, s, m, e);
		}
	}
}

// take first element as pivot
template <typename T>
void quick(T *arr, int s, int e)
{
	int n = e - s;
	if (n <= 1) {
		return;
	}

	// [s + 1, l) < pivot
	// [l, u) >= pivot
	// (u, e] unscanned
	int l = s + 1;
	for (int u = l; u < e; u++) {
		if (arr[u] < arr[s]) {
			exch(arr, u, l++);
		}
	}

	int p = l - 1;
	exch(arr, s, p);
	quick(arr, s, p);
	quick(arr, p + 1, e);
}

// take first element as pivot
template <typename T>
void quick2(T *arr, int s, int e)
{
	int n = e - s;
	if (n <= 1) {
		return;
	}

	// (s, i) <= pivot
	// (j, e) >= pivot
	// [i, j] unscanned
	int i = s + 1;
	int j = e - 1;
	while (true) {
		while (i <= j && arr[i] <= arr[s]) {
			++i;
		}
		while (j >= i && arr[j] >= arr[s]) {
			--j;
		}
		if (i > j) break;
		exch(arr, i++, j--);
	}

	int p = j;
	exch(arr, s, p);
	quick(arr, s, p);
	quick(arr, p + 1, e);
}

// take first element as pivot
template <typename T>
void quick3way(T *arr, int s, int e)
{
	if (e - s <= 1) {
		return;
	}

	// (s, p) < pivot
	// [p, i) == pivot
	// [i, g) unscanned
	// [g, e) > pivot
	int i = s + 1;
	int p = i;
	int g = e;
	while (i < g) {
		if (arr[i] < arr[s]) {
			exch(arr, i++, p++);
		}
		else if (arr[i] == arr[s]) {
			++i;
		}
		else {
			exch(arr, i, --g);
		}
	}

	exch(arr, s, g - 1);
	quick3way(arr, s, p);
	quick3way(arr, g, e);
}

int left(int i) { return i * 2 + 1; }
int right(int i) { return left(i) + 1; }
int parent(int i) { return (i - 1)/ 2; }

template <typename T>
void sink(T *arr, int i, int size)
{
    // i is less than parent
    int l = left(i);
    while (l < size) {
        int c = l;
        int r = l + 1;
        if (r < size && arr[r] > arr[c]) {
            c = r;
        }
        if (arr[i] >= arr[c]) {
            break;
        }
        exch(arr, i, c);
        i = c;
        l = left(i);
    }
}

template <typename T>
void heap(T *arr, int n)
{
    int heap_size = n;
    for (int i = n/2; i >= 0; --i) {
        sink(arr, i, heap_size);
    }

    for (int i = n; i > 0; --i) {
        exch(arr, 0, i - 1);
        sink(arr, 0, i - 1);
    }
}

#endif
