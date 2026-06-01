#pragma once
#include "sorting.hpp"
#include "search.hpp"
#include "hashTable.hpp"
#include "lists.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "binaryTrees.hpp"
#include "graph.hpp"
#include <ctime>

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
  int size, choice = 0, key, value;
  cout << "Enter table size: ";
  cin >> size;
  HashMapTable hashTable(size);
  while(true and choice != 5){
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
        if(value != -1) cout << "Found " << value << endl;
        else cout << "Key wasn`t found" << endl;
        break;
      case 3:
        cout << "Enter key to remove: ";
        cin >> key;
        hashTable.Remove(key);
        break;
      case 4:
        hashTable.Display();
        break;
      case 5:
        exit(0);
        break;
      default:
        cout << "Wrong option" << endl;
    }
  }
}

void DoLists() {
  int choice, value;
  DoubleListNode *mylist = nullptr;
  while(true){
    cout << "Choose operation on list:\n1 - insert element\n2 - remove element\n3 - remove first element\n4 - print\n5 - exit\n $ ";
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
        exit(0);
        break;
      default:
        cout << "Wrong option" << endl;
    }
  }
  DeleteList(mylist);
}

void DoStack() {
  int choice, value;
  SoleListNode *top = nullptr;
  while(true){
    cout << "Choose operation on stack:\n1 - push\n2 - pop\n3 - peek\n4 - exit\n $ ";
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
        exit(0);
        break;
      default:
        cout << "Wrong option" << endl;
    }
  }
}

void DoQueue() {
  int choice, value;
  SoleListNode *front = nullptr;
  SoleListNode *rear = nullptr;
  while(true){
    cout << "Choose operation on queue:\n1 - enqueue\n2 - dequeue\n3 - display\n4 - clear queue\n5 - exit\n $ ";
    cin >> choice;
    switch(choice){
      case 1:
        cout << "Enter a value: ";
        cin >> value;
        rear = enqueue(rear, value);
        if (front == nullptr) front = rear;
        break;
      case 2:
        if (front != nullptr) {
          front = dequeue(front);
          if (front == nullptr) rear = nullptr;
        }
        break;
      case 3:
        Display(front);
        break;
      case 4:
        ClearQueue(front);
        front = rear = nullptr;
        break;
      case 5:
        exit(0);
        break;
      default:
        cout << "Wrong option" << endl;
    }
    cin.clear();
  }
}

void DoBST() {
  int choice, value;
  TreeNode *root = nullptr;
  while(true){
    cout << "Choose operation on BST:\n1 - insert node\n2 - delete node\n3 - search\n4 - in order traversal\n5 - exit\n $ ";
    cin >> choice;
    switch(choice){
      case 1:
        cout << "Enter value to insert: ";
        cin >> value;
        root = Insert(root, value);
        break;
      case 2:
        cout << "Enter value to delete: ";
        cin >> value;
        root = Delete(root, value);
        break;
      case 3:
        cout << "Enter value to search: ";
        cin >> value;
        if (Search(root, value)) cout << "Value " << value << " is present in tree\n";
        else cout << "Value " << value << " is not present in tree\n";
        break;
      case 4:
        InOrderTraversal(root);
        cout << endl;
        break;
      case 5:
        DeleteTree(root);
        exit(0);
        break;
      default:
        cout << "Wrong option" << endl;
    }
  }
  DeleteTree(root);
}

void DoGraph() {
  int choice, value;
  cout << "Enter num of nodes: ";
  cin >> value;
  cin.clear();
  vector<vector<int>> graph = genMatrix(value);
  cleanMatrix(graph);
  vector<vector<int>> weights = genWeights(graph);
  while(true)
  {
    cout << "Choose operation on graph:\n1 - depth search\n2 - breadth search\n3 - Kruskal MST\n4 - print matrix\n5 - print weights\n6 - prim\n7 - dijkastra\n8 - exit\n $";
    cin >> choice;
    switch(choice){
      case 1:
        dfsAllNodes(graph);
        break;
      case 2:
        bfsAllNodes(graph);
        break;
      case 3: {
        int n = weights.size();
        vector<KEdge> kedges;
        for (int i = 0; i < n; ++i)
          for (int j = i + 1; j < n; ++j)
            if (weights[i][j] != 0)
              kedges.push_back({i, j, weights[i][j]});
        vector<KEdge> mst = kruskalMST(n, kedges);
        if (mst.empty()) { cout << "Graph is not connected" << endl; break; }
        int total = 0;
        cout << "Minimum spanning tree:" << endl;
        for (KEdge &e : mst) {
          cout << e.a + 1 << " - " << e.b + 1 << "  weight: " << e.weight << endl;
          total += e.weight;
        }
        cout << "Total weight: " << total << endl;
        break;
      }
      case 4:
        printGraphMatrix(graph);
        break;
      case 5:
        printWeightMatrix(weights);
        break;
      case 6:
        primMST(weights, graph.size());
        break;
      case 7:
        cout << "Enter start vertex: ";
        cin >> value;
        dijkstra(weights, value - 1, graph.size());
        break;
      case 8:
        exit(0);
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
  
  int* ar = new int[size];
  for(int i = 0; i<size; i++) ar[i] = rand()%20;
  
  PrintArray(ar, size, false);
  ChooseArrayOperation(ar, size);
  delete[] ar;
}

void HandTypeArr(int size){
  int* ar = new int[size];
  cout<< "Now enter elements of array: \n";
  for(int i = 0; i < size; i++){
    cout << "Element num " << i+1 << ": ";
    cin >> ar[i];
  }
  ChooseArrayOperation(ar, size);
  delete[] ar;
}

void Exec(){
  cout << "Choose what you`ll do:\n1 - array operations\n2 - hash operations\n3 - do list operations\n4 - do stack\n5 - do queue\n6 - do BST\n7 - do graph\n $ ";
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
    case 5:
      DoQueue();
      break;
    case 6:
      DoBST();
      break;
    case 7:
      DoGraph();
      break;
    default: cout << "Wrong option" << endl;
  }
}

vector<int> ArrGenV(int size=10, int cap=100){
  srand(time(0));
  vector<int> ar;
  for(int i = 0; i<size; i++) ar.push_back(rand()%cap);
  return ar;
}
