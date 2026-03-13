#pragma once
#include <algorithm>
#include <cstdlib>
#include <format>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

void PrintArray(int ar[], int size, bool sorted){
  if(sorted) cout << "\nYour array now sorted:\n";
  else cout << "\nThat`s your new array:\n";
  for(int i = 0; i < size; i++)
    cout << " | " << ar[i];
  cout << " |\n";
}

void SelectionSort(int ar[], int size){
  for(int i = 0; i < size-1; i++){
    int temp = i;
    for(int j = i+1; j < size; j++)
      if(ar[j] < ar[temp]) temp = j;
    swap(ar[i], ar[temp]);
  }
  PrintArray(ar, size, true);
}

void merge(int ar[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = ar[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = ar[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            ar[k] = L[i];
            i++;
        } else {
            ar[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        ar[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        ar[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

void MergeSort(int ar[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    MergeSort(ar, left, mid);
    MergeSort(ar, mid + 1, right);
    merge(ar, left, mid, right);
}

void BubbleSort(int ar[], int size){
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (ar[j] > ar[j + 1]) {
        swap(ar[j], ar[j + 1]);
      }
    }
  }
  PrintArray(ar, size, true);
}

void PasteSort(int ar[], int size){
  for (int j = 1; j < size; j++) {
    int el = 0;
    for(int i = 0; i<=j; i++){
      el = ar[j];
      if(ar[i]>=el){
        ar[j] = ar[i];
        ar[i] = el;
      }
    }
  }
  PrintArray(ar, size, true);
}

int partition(int ar[], int low, int high) {
  int pivot = ar[high];
  int i = low - 1;
  for (int j = low; j < high; j++){
    if(ar[j] <= pivot){
      i++;
      swap(ar[i], ar[j]);
    }
  }
  swap(ar[i+1], ar[high]);
  return i+1;
}

void QuickSort(int ar[], int low, int high){
  if (low < high){
    int pivotIndex = partition(ar, low, high);
    QuickSort(ar, low, pivotIndex - 1);
    QuickSort(ar, pivotIndex + 1, high);
  }
}

void ShellSort(int ar[], int n){
  for(int gap = n/2; gap > 0; gap /= 2){
    for(int i = gap; i < n; i++){
      int temp = ar[i];
      int j;
      for(j = i; j >= gap and ar[j - gap] > temp; j -= gap)
        ar[j] = ar[j - gap];
      ar[j] = temp;
    }
  }
  PrintArray(ar, n, true);
}

void ShakerSort(int ar[], int n){
  bool swapped;
  do {
    swapped = false;
    for(int i = 0; i < n - 1; i++){
      if(ar[i] > ar[i+1]){
        swap(ar[i], ar[i+1]);
        swapped = true;
      }
    }
    if(!swapped) break;
    swapped = false;
    for(int i = n-1; i > 0; --i){
      if(ar[i-1] > ar[i]){
        swap(ar[i-1], ar[i]);
        swapped = true;
      }
    }
  } while(swapped);
  PrintArray(ar, n, true);
}

void heapify(int ar[], int n, int i){
  int largest = i;
  int left = 2 * i + 1; 
  int right = 2 * i + 2;

  if(left < n && ar[left] > ar[largest])
    largest = left;
  if(right < n && ar[right] > ar[largest])
    largest = right;

  if(largest != i){
    swap(ar[i], ar[largest]);
    heapify(ar, n, largest);
  }
}

void HeapSort(int ar[], int n){
  for(int i = n / 2 - 1; i >= 0; --i) 
    heapify(ar, n, i);
  for(int i = n - 1; i > 0; --i){
    swap(ar[0], ar[i]);
    heapify(ar, i, 0); 
  }
}

void ChooseSortMethod(int ar[], int size){
  cout << "Now choose sorting alghorithm:\n1 - selection sort\n2 - bubble sort\n3 - merge sort\n4 - paste sort\n5 - quick sort\n6 - shell sort\n7 - shaker sort\n8 - heap sort\n";
  int choice;
  cin >> choice;
  
  switch (choice) {
    case 1:
      SelectionSort(ar, size);
      break;
    case 2:
      BubbleSort(ar, size);
      break;
    case 3:
      MergeSort(ar, 0, size-1);
      PrintArray(ar, size, true); 
      break;
    case 4:
      PasteSort(ar,size);
      break;
    case 5:
      QuickSort(ar, 0, size-1);
      PrintArray(ar, size, true); 
      break;
    case 6:
      ShellSort(ar, size);
      break;
    case 7:
      ShakerSort(ar, size);
      break;
    case 8:
      HeapSort(ar, size);
      PrintArray(ar, size, true);
      break;
    default:
      cout << "Wrong option";
  }
}

void ArrGen(int size){
  cout << "Enter seed: ";
  int seed;
  cin >> seed;
  srand(seed);
  
  int ar[size];
  for(int i = 0; i<size; i++) ar[i] = rand()%20;
  
  PrintArray(ar, size, false);
  ChooseSortMethod(ar, size);
}

void HandTypeArr(int size){
  int ar[size];
  cout<< "Now enter elements of array: \n";
  for(int i = 0; i < size; i++){
    cout << format("Element num {}: ", i+1);
    cin >> ar[i];
  }
  ChooseSortMethod(ar, size);
}

void Exec(){
  int size;
  char opt;
  cout << "Enter size of an array: ";
  cin >> size;
  cout << "Should we generate array(y), or enter it manually(n)? [y/n]: ";
  cin >> opt;
  
  if(opt == 'y' || opt == 'Y') ArrGen(size);
  else if(opt == 'n' || opt == 'N') HandTypeArr(size);
  else cout << "Wrong option, bye!";
}
