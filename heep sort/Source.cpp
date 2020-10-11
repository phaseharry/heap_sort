#include "HeapSort.h"

#include <iostream>
#include <chrono>
#include <string>

using namespace std;

void runForN(int n, HeapSort &run);
void run50Random(HeapSort &run);

int main() {
	srand((unsigned)time(0));
	HeapSort run = HeapSort();
	runForN(100, run);
	runForN(200, run);
	runForN(300, run);
	runForN(400, run);
	runForN(500, run);
	runForN(1000, run);
	runForN(4000, run);
	runForN(10000, run);
	return 0;
}

void runForN(int n, HeapSort &run) {
	cout << "running for size n: " << n << endl;
	run.resetSizeAndType(0, n);
	run.sort(); // sort an already sorted array
	run.resetArrType(1); // changing init array to a reversely sorted array
	run.sort(); // sort a reverely sorted array
	run.resetArrType(2); // changing init array to a random array
	run.sort(); // sorting a random array
	run.resetFiftyInstancesTracker(); // resetting the totalTime tracker in run object to prepare for the 50x timer run
	run.resetArr(); // resetting the array so we can a totally random initial array
	run50Random(run);
}

void run50Random(HeapSort &run) {
	for (int i = 1; i <= 50; i++) {
		run.sort();
		run.resetArr();
	}
	cout << "50 runs of heap sort on a " << run.getInitArrType() << " array with an initial size of " << run.getSize() << " took a total of " << run.getTotalSteps() << " steps and "
		<< run.getTotalTime() << " microseconds." << endl;
}