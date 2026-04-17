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

struct StackNode {
  int data;
  StackNode *next;

  StackNode(int value) : data(value), next(nullptr) {}
};

StackNode *push(StackNode *top, int value) {
  StackNode *newNode = new StackNode(value);
  newNode->next = top;
  return newNode;
}

StackNode *pop(StackNode *top) {
  if (top != nullptr) {
    StackNode *temp = top;
    top = top->next;
    delete temp;
  }
  return top;
}

int peek(StackNode *top) {
  if (top != nullptr) return top->data;
  return -1;
}

bool isEmpty(StackNode *top) { return top == nullptr; }
