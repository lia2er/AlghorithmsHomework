#pragma once
#include "thingThatLookLikeLib.hpp"
#include "search.hpp"

using namespace std;


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

void ChooseSearchMethod(int ar[], int size){
  int target;
  cout << "Enter target: ";
  cin >> target;
  cout << "Now choose search method:\n1 - linear search\n2 - linear search with barrier\n";
  int choice;
  cin >> choice;
  
  switch (choice) {
    case 1:{
      int result = LinearSearch(ar, size, target);
      CheckReturn(result, target);
      break;}
    case 2:{
      int result = LinearSearchWithBarrier(ar, size, target);
      CheckReturn(result, target);
      break;}
    default:
      cout << "Wrong option";
  }
}

void ChooseOperation(int ar[], int size){
  cout << "Should we search or sort?\n1 - sort\n2 - search\n";
  int option;
  cin >> option;
  switch (option) {
    case 1:
      ChooseSortMethod(ar, size);
      break;
    case 2:
      ChooseSearchMethod(ar, size);
      break;
    default:
      cout << "Wrong operation" << endl;
      break;
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
  ChooseOperation(ar, size);
}

void HandTypeArr(int size){
  int ar[size];
  cout<< "Now enter elements of array: \n";
  for(int i = 0; i < size; i++){
    cout << format("Element num {}: ", i+1);
    cin >> ar[i];
  }
  ChooseOperation(ar, size);
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
