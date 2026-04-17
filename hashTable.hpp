#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>
#include <algorithm>

using namespace std;

struct HashTableEntry{
  int key, value;
};

class HashMapTable{
  private:
    int T_S;
    vector<HashTableEntry> *table;
  public:
    HashMapTable(int size=10){
      T_S = size;
      table = new vector<HashTableEntry>[T_S];
    }
    int HashFunc(int key){return key % T_S;}
    
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

    void Display() {
      for (int i = 0; i < T_S; i++) {
        cout << "Bucket [" << i << "]:";
        
        // If the vector at this index is empty
        if (table[i].empty()) cout << " (empty)";
        else for (const auto& entry : table[i]) 
            cout << " --> Key: " << entry.key 
                      << ", Value: " << entry.value;
          
        cout << endl;
      }
    }
/*
    void Draw(Container list) {
      for (int i = 0; i < T_S; i++) {
        DrawText(format("Bucket [{}]:", i), list.rect.x + gap, list.rect.y + gap, 10, WHITE);
        
        if (table[i].empty()) DrawText(" (empty)", list.rect.x + gap*2, list.rect.y + gap*2, 10, WHITE);
        else for (const auto& entry : table[i]) 
            DrawText(format(" --> Key: {}, Value: {}", entry.key, entry.value), );
          
        cout << endl;
      }
    }*/
    void Draw(int startX, int startY, Color gray, Color red, Color green) {
      const int boxH = 50;
      const int gap = 10;
      const int fontSize = 20;
    
      for (int i = 0; i < T_S; i++) {
        int bucketY = startY + (i * (boxH + gap));
        
        string indexLabel = "[" + to_string(i) + "]";
        int indexTextWidth = MeasureText(indexLabel.c_str(), fontSize);
        int bucketBoxW = std::max(50, indexTextWidth + (gap * 2)); 
    
        DrawRectangleRec({(float)startX, (float)bucketY, (float)bucketBoxW, (float)boxH}, gray);
        DrawRectangleLinesEx({(float)startX, (float)bucketY, (float)bucketBoxW, (float)boxH}, 2, green);
        
        int indexTextX = startX + (bucketBoxW / 2) - (indexTextWidth / 2);
        int indexTextY = bucketY + (boxH / 2) - (fontSize / 2);
        DrawText(indexLabel.c_str(), indexTextX, indexTextY, fontSize, WHITE);
    
        int currentX = startX + bucketBoxW; 
    
        for (const auto& entry : table[i]) {
          string label = to_string(entry.key) + ":" + to_string(entry.value);
          int textWidth = MeasureText(label.c_str(), fontSize);
          int dynamicBoxW = max(50, textWidth + (gap * 2)); 
    
          DrawLine(currentX, bucketY + boxH/2, currentX + gap, bucketY + boxH/2, red);
          currentX += gap;
    
          Rectangle rec = {(float)currentX, (float)bucketY, (float)dynamicBoxW, (float)boxH};
          DrawRectangleRec(rec, gray);
          DrawRectangleLinesEx(rec, 2, green);
    
          int textX = currentX + (dynamicBoxW / 2) - (textWidth / 2);
          int textY = bucketY + (boxH / 2) - (fontSize / 2);
          DrawText(label.c_str(), textX, textY, fontSize, WHITE);
    
          currentX += dynamicBoxW;
        }
      }
    }
    
    ~HashMapTable(){delete[] table;}

};

