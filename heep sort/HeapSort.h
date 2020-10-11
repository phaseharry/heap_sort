#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>
#include <string>
#include <chrono>

using namespace std;

class HeapSort {
private:
	int arrType; // used to determine if our array will be sorted, reverseSorted, or random : 0, 1, 2, respectively
	vector<int> arr;
	vector<int> generateSorted(int newSize);
	vector<int> generateReverseSorted(int newSize);
	vector<int> generateRandom(int newSize);
	vector<int> setArr(int initArr, int newSize);
	void buildHeap(vector<int> &arr, int &steps);
	void siftDown(int startIdx, int endIdx, vector<int>& heap, int &steps);
	void swap(int idx1, int idx2, vector<int>& heap, int &steps);
	long long totalDurationInMicroSecs;
	int totalSteps;
	int size;
public:
	HeapSort();
	HeapSort(int initArr, int newSize);
	int getSize() const;
	long long getTotalTime();
	int getTotalSteps();
	void sort();
	void printArr() const;
	void resetArr();
	void resetFiftyInstancesTracker();
	void resetSize(int newSize);
	void resetArrType(int initArr);
	void resetSizeAndType(int initArr, int newSize);
	string getInitArrType() const;
};

#endif