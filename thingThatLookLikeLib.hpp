#pragma once
#include <cstdlib>
#include <format>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

void PrintArr(int ar[], int size){
  for(int i = 0; i < size; i++)
    cout << " | " << ar[i];
  cout << " |\n";
}

void SelectionSorting(int ar[], int size){
  int temp;
  cout << "Your array now sorted!" << endl;
  for(int i = 0; i < size-1; i++){
    temp = i;
    for(int j = i+1; j < size; j++)
      if(ar[j] < ar[temp]) temp = j;
    swap(ar[i], ar[temp]);
  }
  PrintArr(ar, size);
}

void ArrGen(int size){
  cout << "Enter seed: ";
  int seed;
  cin >> seed;
  srand(seed);
  int ar[size];
  for(int i = 0; i<size; i++) ar[i] = rand()%20;
  cout << "That`s your new array: \n";
  PrintArr(ar, size);
  SelectionSorting(ar,size);
}

void HandTypeArr(int size){
  int ar[size];
  cout<< "Now enter elements of array: \n";
  for(int i = 0; i < size; i++){
    cout << format("Element num {}: ", i+1);
    cin >> ar[i];
  }
  SelectionSorting(ar, size);
}

