#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct HashTableEntry{
  int key, value;
};

class HashMapTable{
  private:
    int T_S;
    vector<HashTableEntry> *table;
  public:
    HashMapTable(int size){
      T_S = size;
      table = new vector<HashTableEntry>[T_S];
    }

    int HashFunc(int key){
      return key % T_S;
    }
    
    void Insert(int key, int value){
      int index = HashFunc(key);
      HashTableEntry entry = {key, value};
      table[index].push_back(entry);
    }
    
    int SearchKey(int key){
      int index = HashFunc(key);
      for( const HashTableEntry &entry : table[index])
        if(entry.key == key) return entry.value;
      return -1;
    }
    
    void Remove(int key){
      int index = HashFunc(key);
      for(auto it = table[index].begin();
          it != table[index].end(); ++it){
        if(it->key == key){
          table[index].erase(it);
          return;
        }
      }
    }
    
    ~HashMapTable(){
      delete[] table;
    }
};

