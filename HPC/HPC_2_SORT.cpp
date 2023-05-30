#include<iostream>
#include<omp.h>

using namespace std;

void pbubblesort(int v[], int n) {
	for(int i=0; i<n; i++) {
		int first = i % 2;
		#pragma omp parallel for shared(v, first)
		for(int j=first; j<n-1; j+=2) {
			if(v[j]> v[j+1])
				swap(v[j], v[j+1]);
		}
	}
}

void bubblesort(int v[], int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n-1; j++) {
			if(v[j]> v[j+1])
				swap(v[j], v[j+1]);
		}
	}
}

int main() {
	int n;
	cout<<"Enter the number of elements: ";
	cin>>n;
	
	int v1[];
	int v2[];

  cout<<"Enter numbers one by one: ";
	for(int i=0; i<n; i++) {
		cin>>v1[i];
	}

	v2 = v1;

	int startTime = omp_get_wtime();
	bubblesort(v1, n);
	int endTime = omp_get_wtime();
	cout<<"Time taken for sequential execution: "<<endTime-startTime<<" seconds";

	for(int i=0; i<n; i++) {
		cout<<v1[i]<<" ";
	}

	startTime = omp_get_wtime();
	pbubblesort(v2, n);
	endTime = omp_get_wtime();
	cout<<"Time taken for parallel execution: "<<endTime-startTime<<" seconds";

	for(int i=0; i<n; i++) {
		cout<<v2[i]<<" ";
	}
}

// g++ -fopenmp 2_parallel_bubble.cpp -o a.o && ./a.o