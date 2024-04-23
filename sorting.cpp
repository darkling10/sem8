
#include <bits/stdc++.h>
#include <ctime>
#include <omp.h>

using namespace std;

//function to generate array with random numbers
vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    srand(time(0)); // Seed for random number generation

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    }

    return arr;
}

// Function to perform bubble sort
void bubbleSort(vector<int>& arr) {
    bool swapped;
    int n = arr.size();
    do {
        swapped = false;
        #pragma omp parallel for
        for (int i = 1; i < n; i += 2) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        #pragma omp parallel for
        for (int i = 2; i < n; i += 2) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
    } while (swapped);
}

// Function to merge two halves of the array
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= m) {
        temp[k++] = arr[i++];
    }

    while (j <= r) {
        temp[k++] = arr[j++];
    }

    for (i = l, k = 0; i <= r; i++, k++) {
        arr[i] = temp[k];
    }
}

// Function to perform merge sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);
            
            #pragma omp section
            mergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

void printArray(vector<int>& result){
  for(int x : result){
    cout << x << " ";
  }
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "\nOriginal array:\n";
    arr = generateRandomArray(n);
    // printArray(arr);
    cout << "\n";

    // Parallel Bubble Sort
    cout << "\nSorting array with Parallel Bubble Sort...\n";
    clock_t startTime = clock();
    bubbleSort(arr);
    clock_t endTime = clock();
    cout << "\nSorted array:\n";
    // printArray(arr);
    double elaspedTime = double(endTime-startTime)/CLOCKS_PER_SEC;
    cout << "\nTime taken: " << fixed << setprecision(5) << elaspedTime << " seconds\n";

    // Reinitialize the array for Merge Sort
    arr = generateRandomArray(n);

    // Parallel Merge Sort
    cout << "\nSorting array with Parallel Merge Sort...\n";
    startTime = clock();
    mergeSort(arr, 0, n - 1);
    endTime = clock();
    double elaspedTime2 = double(endTime-startTime)/CLOCKS_PER_SEC;
    cout << "\nSorted array:\n";
    // printArray(arr);
    cout << "\nTime taken: " << fixed << setprecision(5)  << elaspedTime2 << " seconds\n";

    return 0;
}

// Command to compile : g++ -fopenmp -o bmsort bmsort.cpp
// Command to execute : ./bmsort
// Sample input : 10

  /*
  #include<iostream>
  #include<omp.h>
  #include<ctime>
  #include<cstdlib>

  using namespace std;

  void sequentialbubble(int arr[],int n ){
  for(int i=0;i<n-1;++i){
    for(int j= 0 ;j<n-i-1;++j){
      if(arr[j]>arr[j+1]){
        swap(arr[j],arr[j+1]);
    }
  }
  }
  }

  void parallelbubble(int arr[],int n){
  #pragma omp parallel for shared(arr)
  for(int i=0;i<n-1;++i){
    for(int j= 0 ;j<n-i-1;j+=2){
      if(arr[j]>arr[j+1]){
        swap(arr[j],arr[j+1]);
    }
  }
  }
  }

  void generaterandomarray(int arr[],int n){
  srand(time(NULL));
  for(int i = 0;i<n;i++){
    arr[i]=rand()%10000;
  }
  }

  void displayarray(int arr[],int n){
  for(int i=0;i<n;++i){
    cout<<arr[i];
  }

  cout<<endl;
  }

  int main(){

  const int size = 10000;
  int arr[size];

  generaterandomarray(arr,size);

  clock_t startTime=clock();
  sequentialbubble(arr,size);
  clock_t endTime=clock();
  cout<<"performance:"<<double(endTime-startTime)/CLOCKS_PER_SEC<<"seconds"<<endl;;

  generaterandomarray(arr,size);

  startTime= clock();
  parallelbubble(arr,size);
  endTime=clock();
  cout<<"performance:"<<double(endTime-startTime)/CLOCKS_PER_SEC<<"seconds"<<endl;;

  return 0;

  }

  */