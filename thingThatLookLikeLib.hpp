#pragma once
#include <algorithm>
#include <cctype>
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
  int temp;
  for(int i = 0; i < size-1; i++){
    temp = i;
    for(int j = i+1; j < size; j++)
      if(ar[j] < ar[temp]) temp = j;
    swap(ar[i], ar[temp]);
  }
  PrintArray(ar, size, true);
}

void merge(int ar[], int left, int mid, int right){
                       
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
      L[i] = ar[left + i];
  for (int j = 0; j < n2; j++)
      R[j] = ar[mid + 1 + j];

  int i = 0, j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      ar[k] = L[i];
      i++;
    }
    else {
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

}

void MergeSort(int ar[], int left, int right){
  if (left >= right)
    return;

  int mid = left + (right - left) / 2;
  MergeSort(ar, left, mid);
  MergeSort(ar, mid + 1, right);
  merge(ar, left, mid, right);
  PrintArray(ar, right, true);
}

void BubbleSort(int ar[], int size){
  bool swapped;
  for (int i = 0; i < size - 1; i++) {
    swapped = false;
    for (int j = 0; j < size - i - 1; j++) {
      if (ar[j] > ar[j + 1]) {
        swap(ar[j], ar[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) break;
  }
  PrintArray(ar, size, true);
}

void InsertSort(int ar[], int size){
  for (int i = 1; i < size; ++i) {
    int key = ar[i];
    int j = i - 1;
    while (j >= 0 && ar[j] > key) {
      ar[j + 1] = ar[j];
      j = j - 1;
    }
    ar[j + 1] = key;
  }
  PrintArray(ar, size, true);
}

void ChooseSort(int ar[], int size){
  cout << "Now choose sorting alghorithm:\ns - selection sort\nb - bubble sort\nm - merge sort\ni - insert sort\n";
  char choice;
  cin >> choice;
  tolower(choice);
  switch (choice) {
    case 's':
      SelectionSort(ar, size);
      break;
    case 'b':
      BubbleSort(ar, size);
      break;
    case 'm':
      MergeSort(ar, 0, size-1);
      break;
    case 'i':
      InsertSort(ar,size);
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
  ChooseSort(ar, size);
}

void HandTypeArr(int size){
  int ar[size];
  cout<< "Now enter elements of array: \n";
  for(int i = 0; i < size; i++){
    cout << format("Element num {}: ", i+1);
    cin >> ar[i];
  }
  ChooseSort(ar, size);
}

void Exec(){
  int size;
  char opt;
  cout << "Enter size of an array: ";
  cin >> size;
  cout << "Should we generate array(y), or enter it manually(n)? [y/n]: ";
  cin >> opt;
  if(opt == 'y' or 'Y') ArrGen(size);
  else if(opt == 'n' or 'N') HandTypeArr(size);
  else cout << "Wrong option, bye!";
}
