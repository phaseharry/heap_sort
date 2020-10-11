#include "HeapSort.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

HeapSort::HeapSort() {
	arr = generateSorted(100);
	size = 100;
	totalSteps = 0;
	arrType = 0;
	totalDurationInMicroSecs = 0;
}

HeapSort::HeapSort(int initArr, int newSize) {
	size = newSize;
	arrType = initArr;
	totalSteps = 0;
	totalDurationInMicroSecs = 0;
	arr = setArr(initArr, newSize);
}

vector<int> HeapSort::generateSorted(int newSize) {
	vector<int> arr;
	for (int i = 1; i <= newSize; i++) {
		arr.push_back(i);
	}
	return arr;
}

vector<int> HeapSort::generateReverseSorted(int newSize) {
	vector<int> arr;
	for (int i = newSize; i >= 1; i--) {
		arr.push_back(i);
	}
	return arr;
}

vector<int> HeapSort::generateRandom(int newSize) {
	vector<int> arr;
	for (int i = 1; i <= newSize; i++) {
		int randomNumber = (rand() % newSize) + 1;
		arr.push_back(randomNumber);
	}
	return arr;
}

void HeapSort::printArr() const {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl << endl;
}

// used to determine whether our array is going be sorted, reverseSorted, or random before we run a sorting algorithm
vector<int> HeapSort::setArr(int initArr, int newSize) {
	switch (initArr) {
	case 0:
		return generateSorted(newSize);
	case 1:
		return generateReverseSorted(newSize);
	case 2:
		return generateRandom(newSize);
	default:
		return generateSorted(newSize);
	}
}

// used to get the name of the arr type we're sorting
string HeapSort::getInitArrType() const {
	switch (arrType) {
	case 0:
		return "sorted";
	case 1:
		return "reverse sorted";
	case 2:
		return "random";
	default:
		return "";
	}
}

// used to reset how our initial array should look like before sort (sorted, reverseSorted, or random) and rebuilds it
void HeapSort::resetArrType(int initArr) {
	// set arrType
	switch (initArr) {
	case 0:
		arrType = 0;
		break;
	case 1:
		arrType = 1;
		break;
	case 2:
		arrType = 2;
		break;
	default:
		arrType = 0;
		break;
	}
	resetArr();
}

// used for resetting both the initial array type (sorted, reverse sorted, random) and size of array
void HeapSort::resetSizeAndType(int initArr, int newSize) {
	size = newSize;
	resetArrType(initArr);
}

// changes the size property of the Sort object and creates a new vector of newSize
void HeapSort::resetSize(int newSize) {
	size = newSize;
	resetArr();
}
// used to remove the old data from memory and reset the array after every instance run
void HeapSort::resetArr() {
	arr.clear();
	vector<int>().swap(arr);
	arr = setArr(arrType, size);
}

// returns total duration of n runs in microseconds
long long HeapSort::getTotalTime() {
	return totalDurationInMicroSecs;
}

// returns the total steps of n runs
int HeapSort::getTotalSteps() {
	return totalSteps;
}

// gets the size of the array we're working with
int HeapSort::getSize() const {
	return size;
}

// resets the total time of the Sort instance if we're not keeping track of total time for multiple runs
void HeapSort::resetFiftyInstancesTracker() {
	totalDurationInMicroSecs = 0;
	totalSteps = 0;
}

// building a MaxHeap
void HeapSort::buildHeap(vector<int> &array, int &steps) {
	int firstParentIdx = (size - 2) / 2; // getting the first parent idx of our array
	for (int i = firstParentIdx; i >= 0; i--) { // siftDown each parent to their correct positions in a min heap
		siftDown(i, size - 1, array, steps);
	}
}

// used to put each element in the correct spot that would make the array a heap
void HeapSort::siftDown(int startIdx, int endIdx, vector<int>& heap, int &steps) {
	int firstChildIdx = startIdx * 2 + 1; // getting the first child of the parentIdx (startIdx)
	steps++;
	while (firstChildIdx <= endIdx) { // do this operation as long as we have a childIdx to compare to current parentIdx
		// if the 2nd childIdx is within the bounds of the array, then compare it with the first childIdx, else assign -1
		int secondChildIdx = (startIdx * 2 + 2) <= endIdx ? (startIdx * 2 + 2) : -1; 
		int toCompareWithParentIdx;
		steps++;
		if (secondChildIdx != -1 && heap[secondChildIdx] > heap[firstChildIdx]) {
			toCompareWithParentIdx = secondChildIdx;
		} else {
			toCompareWithParentIdx = firstChildIdx;
		}
		steps++;
		// comparing the smaller of the 2 children to the parent. if it is smaller than parent, swap places
		// with the parentIdx and continue to siftDown with the startIdx tracking the idx that was swapped with the old startIdx
		// else if it was not smaller that the parent, then the node is at the correct spot that would make it a heap
		// and we would break out of the siftDown calls
		if (heap[toCompareWithParentIdx] > heap[startIdx]) {
			swap(toCompareWithParentIdx, startIdx, heap, steps);
			startIdx = toCompareWithParentIdx;
			firstChildIdx = startIdx * 2 + 1;
			steps += 3;
		} else {
			break;
		}
	}
}

void HeapSort::swap(int idx1, int idx2, vector<int>& heap, int &steps) {
	int temp = heap[idx1];
	heap[idx1] = heap[idx2];
	heap[idx2] = temp;
	steps += 3;
}

void HeapSort::sort() {
	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	int steps = 0, unsortedIdx = 0, sortedIdx = size - 1;
	// building a max heap and constantly getting the back value and putting it in the back of the sorted sub arr
	buildHeap(arr, steps);
	for (int unsortedIdx = size - 1; unsortedIdx > 0; unsortedIdx--) {
		swap(0, unsortedIdx, arr, steps); // swapping the unsortedIdx with our first element because our first element is the max heap value
		// now that our heap order is messed up, we have to siftDown the 0th idx value to its proper position. 
		// we only go up to the unsortedIdx - 1 because current value of unsortedIdx is sorted in this iteration after the swap
		siftDown(0, unsortedIdx - 1, arr, steps);
	}
	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	auto thisDuration = duration_cast<microseconds>(endTime - startTime);
	cout << "Heap sort took " << steps << " number of steps and " << thisDuration.count()
		<< " microseconds for a " << getInitArrType() << " array" << endl;
	totalSteps += steps;
	totalDurationInMicroSecs += thisDuration.count();
}

