#pragma once
#include "sorting.hpp"
#include "search.hpp"
#include "hashTable.hpp"
#include "lists.hpp"
#include "stack.hpp"
#include <ctime>
#include <format>

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
  cout << "Now choose search method:\n1 - linear search\n2 - linear search with barrier\n3 - binary search\n";
  int choice;
  cin >> choice;
  int result;
  
  switch (choice) {
    case 1:
      result = LinearSearch(ar, size, target);
      CheckReturn(result, target);
      break;
    case 2:
      result = LinearSearchWithBarrier(ar, size, target);
      CheckReturn(result, target);
      break;
    case 3:
      BubbleSort(ar, size);
      result = BinarySearch(ar, size, target);
      CheckReturn(result, target);
      break;
    default:
      cout << "Wrong option";
  }
}

void DoHash(){
  int size, choice, key, value;
  cout << "Enter table size: ";
  cin >> size;
  HashMapTable hashTable(size);
  while(true){
    cout << "Choose operation on hash table:\n1 - insert element\n2 - find an element\n3 - remove element\n4 - print\n5 - quit\n $ ";
    cin >> choice;
    switch(choice){
      case 1:
        cout << "Enter a key: ";
        cin >> key;
        cout << "Enter a value: ";
        cin >> value;
        hashTable.Insert(key, value);
        break;
      case 2:
        cout << "enter a key to search for: ";
        cin >> key;
        value = hashTable.SearchKey(key);
        if(value != 1) cout << "Found " << value << endl;
        else cout << "Key wasn`t found" << endl;
        break;
      case 3:
        cout << "Enter key to remove: ";
        cin >> key;
        hashTable.Remove(key);
        break;
      case 5:
        return;
      case 4:
        hashTable.Display();
        break;
      default:
        cout << "Wrong option" << endl;
    }
  }
}

void DoLists() {
  int choice, value;
  ListNode *mylist = nullptr;
  while(true){
    cout << "Choose operation on list:\n1 - insert element\n2 - remove element\n3 - remove first element\n4 - print\n5 - quit\n $ ";
    cin >> choice;
    switch(choice){
      case 1:
        cout << "Enter a value: ";
        cin >> value;
        mylist = Insert(mylist, value);
        break;
      case 2:
        cout << "enter value to delete it: ";
        cin >> value;
        mylist = DeleteByValue(mylist, value);
        break;
      case 3:
        DeleteFirst(mylist);
        break;
      case 4:
        Display(mylist);
        break;
      case 5:
        break;
      default:
        cout << "Wrong option" << endl;
    }
  }
  DeleteList(mylist);
}

void DoStack() {
  int choice, value;
  StackNode *top = nullptr;
  while(true){
    cout << "Choose operation on stack:\n1 - push\n2 - pop\n3 - peek\n4 - quit\n $ ";
    cin >> choice;
    switch(choice){
      case 1:
        cout << "Enter a value: ";
        cin >> value;
        top = push(top, value);
        break;
      case 2:
        top = pop(top);
        break;
      case 3:
        CheckReturn(peek(top));
        break;
      case 4:
        break;
      default:
        cout << "Wrong option" << endl;
    }
  }
}

void ChooseArrayOperation(int ar[], int size){
  cout << "What you`ll do?\n1 - sort\n2 - search\n $ ";
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
  ChooseArrayOperation(ar, size);
}

void HandTypeArr(int size){
  int ar[size];
  cout<< "Now enter elements of array: \n";
  for(int i = 0; i < size; i++){
    cout << format("Element num {}: ", i+1);
    cin >> ar[i];
  }
  ChooseArrayOperation(ar, size);
}


void Exec(){
  cout << "Choose what you`ll do:\n1 - array operations\n2 - hash operations\n3 - do list operations\n4 - do stack\n $ ";
  char opt;
  int size;
  cin >> size;
  switch(size){
    case 1:
      cout << "Enter size of an array: ";
      cin >> size;
      cout << "Should we generate array(y), or enter it manually(n)? [y/n]: ";
      cin >> opt;
      
      if(tolower(opt) == 'y') ArrGen(size);
      else if(tolower(opt) == 'n') HandTypeArr(size);
      else cout << "Wrong option, bye!";
    break;
    case 2:
      DoHash();
      break;
    case 3:
      DoLists();
      break;
    case 4:
      DoStack();
      break;
    default: cout << "Wrong option" << endl;
  }
}

// things for vectors, everything else is the same

vector<int> ArrGenV(int size=10, int cap=100){
  srand(time(0));
  vector<int> ar;
  for(int i = 0; i<size; i++) ar.push_back(rand()%cap);
  return ar;
}

