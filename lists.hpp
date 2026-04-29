#pragma once
#include <iostream>
#include <raylib.h>

using namespace std;

struct DoubleListNode{
  int data;
  DoubleListNode* next;
  DoubleListNode* prev;

  DoubleListNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

DoubleListNode* Insert(DoubleListNode* head, int value){
  DoubleListNode* newNode = new DoubleListNode(value);
  newNode->next = head;
  if(head != nullptr) head->prev = newNode;
  return newNode;
}

void DeleteList(DoubleListNode* head) {
  while(head != nullptr) {
    DoubleListNode* next = head->next;
    delete head;
    head = next;
  }
}

DoubleListNode* DeleteByValue(DoubleListNode* head, int value) {
  if (head == nullptr) return nullptr;
  DoubleListNode* current = head;

  while (current != nullptr && current->data != value) {
    current = current->next;
  }

  if (current == nullptr) return head;

  if (current == head) {
    head = current->next;
    if (head != nullptr) head->prev = nullptr;
  }

  else {
    if (current->prev != nullptr) current->prev->next = current->next;
    if (current->next != nullptr) current->next->prev = current->prev;
  }

  delete current;
  return head;
}


DoubleListNode* DeleteFirst(DoubleListNode* head){
  if(head == nullptr) return nullptr;
  DoubleListNode* newHead = head->next;
  delete head;
  if(newHead != nullptr) newHead->prev = nullptr;
  return newHead;
}

void Display(DoubleListNode* head){
  DoubleListNode* current = head;
  while(current != nullptr){
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;
}

