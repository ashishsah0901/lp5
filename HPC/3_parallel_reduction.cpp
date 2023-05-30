#include<iostream>
#include<omp.h>

using namespace std;

int minval(int arr[], int n){
  int min = arr[0];
  #pragma omp parallel for reduction(min : min)
  {
    for(int i = 1; i < n; i++){
      if(arr[i] < min) min = arr[i];
    }
  }
  return min;
}

int maxval(int arr[], int n){
  int max = arr[0];
  #pragma omp parallel for reduction(max : max)
  {
    for(int i = 1; i < n; i++){
      if(arr[i] > max) max = arr[i];
    }
  }
  return max;
}

int sum(int arr[], int n){
  int s = 0;
  #pragma omp parallel for reduction(+ : s)
  {
    for(int i = 0; i < n; i++){
      s += arr[i];
    }
  }
  return s;
}

int average(int arr[], int n) {
  return (double)sum(arr, n) / n;
}

int main(){
  int n;
  cout<<"Enter the number of elements: ";
  cin>>n;
  int arr[n];
  cout<<"Enter numbers one by one: ";
  for (int i = 0; i < n; i++) {
    cin>>arr[i];
  }
  cout << "The minimum value is: " << minval(arr, n) << '\n';
  cout << "The maximum value is: " << maxval(arr, n) << '\n';
  cout << "The summation is: " << sum(arr, n) << '\n';
  cout << "The average is: " << average(arr, n) << '\n';
  return 0;
}

// g++ -fopenmp 2_parallel_bubble.cpp -o a.o && ./a.o