#pragma once
#include <iostream>
#include "stack.hpp"

using namespace std;

int queueData[MAX_SIZE];
int front = -1,
    rear = -1;

void enqueu(int value) {
  if (rear == MAX_SIZE -1) {
    cout << "Queue is full" << endl;
    return;
  }
  if (front == -1) front = 0;
  queueData[++rear] = value;
  cout << "Added " << value << " to queue" << endl;
}

void dequeue() {
  if (front == -1) {
    cout << "Queue is empty" << endl;
    return;
  }
  int value = queueData[front];
  cout << "Removed " << value << "from queue" << endl;
  if (front == rear) front = rear = -1;
  else front++;
}

void Display() {
  if (front == -1) {
    cout << "Queue is empty" << endl;
    return;
  }
  cout << "Queue elements: ";
  for (int i = front; i <= rear; i++) cout << queueData[i] << " ";
  cout << endl;
}

SoleListNode *enqueue(SoleListNode *rear, int value) {
  SoleListNode *newNode = new SoleListNode(value);
  if (rear == nullptr) return newNode;
  else {
    rear->next = newNode;
    return newNode;
  }
}

SoleListNode *dequeue(SoleListNode *front) {
  if (front == nullptr) return nullptr;
  else {
    SoleListNode *temp = front;
    front = front->next;
    delete temp;
    return front;
  }
}

void Display(SoleListNode *front) {
  SoleListNode *current = front;
  while (current != nullptr) {
    std::cout << current->data << " ";
    current = current->next;
  }
  std::cout << std::endl;
}

void ClearQueue(SoleListNode *front) {
  while (front != nullptr) {
    SoleListNode *next = front->next;
    delete front;
    front = next;
  }
}
