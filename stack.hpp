#pragma once
#include <iostream>

using namespace std;
static const int MAX_SIZE = 100;
int stackData[MAX_SIZE];
int top = -1;
bool isEmpty() { return top == -1; }

bool isFull() { return top == MAX_SIZE; }

void push(int value) {
  if (isFull()) cout << "Stack might overflow" << endl;
  else {
    stackData[++top] = value;
    cout << "Added: " << value << endl;
  }
}

void pop() {
  if (isEmpty()) cout << "Stack is empty" << endl;
  else cout << "Removed: " << stackData[top--] << endl;
}

void display() {
  if (isEmpty()) cout << "Stack is empty" << endl;
  else {
    cout << "Stack elements: ";
    for(int i = 0; i <= top; ++i) cout << stackData[i] << " ";
    cout << endl;
  }
}

struct SoleListNode {
  int data;
  SoleListNode *next;

  SoleListNode(int value) : data(value), next(nullptr) {}
};

SoleListNode *push(SoleListNode *top, int value) {
  SoleListNode *newNode = new SoleListNode(value);
  newNode->next = top;
  return newNode;
}

SoleListNode *pop(SoleListNode *top) {
  if (top != nullptr) {
    SoleListNode *temp = top;
    top = top->next;
    delete temp;
  }
  return top;
}

int peek(SoleListNode *top) {
  if (top != nullptr) return top->data;
  return -1;
}

bool isEmpty(SoleListNode *top) { return top == nullptr; }
