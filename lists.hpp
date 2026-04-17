#pragma once
#include <iostream>
#include <raylib.h>

using namespace std;

struct ListNode{
  int data;
  ListNode* next;
  ListNode* prev;

  ListNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

ListNode* Insert(ListNode* head, int value){
  ListNode* newNode = new ListNode(value);
  newNode->next = head;
  if(head != nullptr) head->prev = newNode;
  return newNode;
}

void DeleteList(ListNode* head) {
  while(head != nullptr) {
    ListNode* next = head->next;
    delete head;
    head = next;
  }
}

ListNode* DeleteByValue(ListNode* head, int value) {
  if (head == nullptr) return nullptr;
  ListNode* current = head;

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


ListNode* DeleteFirst(ListNode* head){
  if(head == nullptr) return nullptr;
  ListNode* newHead = head->next;
  delete head;
  if(newHead != nullptr) newHead->prev = nullptr;
  return newHead;
}

void Display(ListNode* head){
  ListNode* current = head;
  while(current != nullptr){
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;
}

