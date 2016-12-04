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

#endif
