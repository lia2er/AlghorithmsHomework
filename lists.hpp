#pragma once
#include <iostream>
#include <raylib.h>

using namespace std;

struct Node{
  int data;
  Node* next;
  Node* prev;

  Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

Node* Insert(Node* head, int value){
  Node* newNode = new Node(value);
  newNode->next = head;
  if(head != nullptr) head->prev = newNode;
  return newNode;
}

void DeleteList(Node* head) {
  while(head != nullptr) {
    Node* next = head->next;
    delete head;
    head = next;
  }
}

Node* DeleteByValue(Node* head, int value) {
  if (head == nullptr) return nullptr;
  Node* current = head;

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


Node* DeleteFirst(Node* head){
  if(head == nullptr) return nullptr;
  Node* newHead = head->next;
  delete head;
  if(newHead != nullptr) newHead->prev = nullptr;
  return newHead;
}

void Display(Node* head){
  Node* current = head;
  while(current != nullptr){
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;
}

