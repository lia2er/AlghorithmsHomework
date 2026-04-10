#pragma once
#include <iostream>
#include "sorting.hpp"

using namespace std;

int LinearSearch(int ar[], int n, int target){
  for(int i = 0; i < n; i++)
    if(ar[i] == target) return i;
  return -1;
}

int LinearSearchWithBarrier(int ar[], int n, int target){
  int lastValue = target;
  ar[n-1] = target;

  int i = 0;
  while(ar[i] != target) ++i;
  ar[n-1] = lastValue;

  if(i < n - 1 or ar[n - 1] == target) return i;
  else return -1;
}

int BinarySearch(int ar[], int size, int target){
  int left = 0,
      right = size - 1;
  while(left <= right){
    int mid = left + (right - left) / 2;
    if(ar[mid] == target) return mid;
    if (ar[mid] < target) left = mid + 1;
    else right = mid - 1;
  }
  return -1;
}

void CheckReturn(int result, int target){
  if(result != -1) cout << "Значення " << target << " знайдено на позиції " << result + 1 << endl;
  else cout << "Значення " << target << " не знайдено у масиві" << endl;
}

// the same but for vectors


int LinearSearch(vector<int> ar, int n, int target){
  for(int i = 0; i < n; i++)
    if(ar[i] == target) return i;
  return -1;
}

int LinearSearchWithBarrier(vector<int> ar, int n, int target){
  int lastValue = target;
  ar[n-1] = target;

  int i = 0;
  while(ar[i] != target) ++i;
  ar[n-1] = lastValue;

  if(i < n - 1 or ar[n - 1] == target) return i;
  else return -1;
}

int BinarySearch(vector<int> ar, int size, int target){
  int left = 0,
      right = size - 1;
  while(left <= right){
    int mid = left + (right - left) / 2;
    if(ar[mid] == target) return mid;
    if (ar[mid] < target) left = mid + 1;
    else right = mid - 1;
  }
  return -1;
}

string CheckReturnToString(int result, int target){
  if(result != -1) return format("Значення {} знайдено на позиції {}\n", target, result + 1);
  else return format("Значення {} не знайдено у масиві\n", target);
}
