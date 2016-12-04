#ifndef SORT_H
#define SORT_H

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

#endif
