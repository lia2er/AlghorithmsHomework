#pragma once
#include <iostream>
#include <raylib.h>
#include <string>
#include <ranges>
#include <vector>
#include <format>
#include <algorithm>
#include "hashTable.hpp"
#include "sorting.hpp"
#include "search.hpp"
#include "utility.hpp"
#include "lists.hpp"

using namespace std;

const int screenWidth = 800;
const int screenHeight = 800;
const int gap = 15;
const int nodeWidth = 40,
          nodeHeight = 50,
          horizontalSpacing = 10;
vector<int> parsedArray;
vector<int> sortedArray;
int searchTarget;
int newSearchTarget;
int searchResult;
string stringSearchTarget;
string stringToParse;
bool isTextFocused = false;
HashMapTable hashTable(10);
int hashKeyInput;
int hashValueInput;
string hashKeyString;
string hashValueString;
bool isKeyFieldFocused = false,
     isValueFieldFocused = false;
Node *mylist = nullptr;

const Color green = {0x98, 0x97, 0x1a, 255},
      yellow = {0xd7, 0x99, 0x21, 255},
      blue = {0x45, 0x85, 0x88, 255},
      black = {0x28, 0x28, 0x28, 255},
      black2 = {0x3c, 0x38, 0x36, 255},
      gray = {0x50, 0x49, 0x45, 255},
      red = {0xcc, 0x24, 0x1d, 255};

typedef struct Button {
    Rectangle rect;
    Color color;
} Button;

// One-line initializations: { {x, y, width, height}, color }
Button button_Sorting       = { { 10, 10, 150, 50 }, gray };
Button button_Searching     = { { 170, 10, 150, 50 }, gray };
Button button_Hash          = { { 330, 10, 150, 50 }, gray };
Button button_Lists = { {490, 10, 150, 50}, gray};
// sorting buttons
Button button_SelectionSort = { { 10, 70, 150, 50 }, gray };
Button button_BubbleSort    = { { 10, 130, 150, 50 }, gray };
Button button_MergeSort     = { { 10, 190, 150, 50 }, gray };
Button button_PasteSort     = { { 10, 250, 150, 50 }, gray };
Button button_QuickSort     = { { 10, 310, 150, 50 }, gray };
Button button_ShellSort     = { { 10, 370, 150, 50 }, gray };
Button button_ShakerSort    = { { 10, 430, 150, 50 }, gray };
Button button_HeapSort      = { { 10, 490, 150, 50 }, gray };
// searching buttons
Button button_LinearSearch = button_SelectionSort;
Button button_LinearSearchWithBarrier = button_BubbleSort;
Button button_BinarySearch = button_MergeSort;
// Hash buttons
Button button_HashInsert = button_SelectionSort;
Button button_HashRemove = button_BubbleSort;
Button button_HashSearch = button_MergeSort;
// action buttons
Button button_GenerateArray = { { screenWidth - 150, 70, 150, 50 }, gray };
Button button_Run = { { button_GenerateArray.rect.x, button_GenerateArray.rect.y + 60, button_GenerateArray.rect.width, button_GenerateArray.rect.height }, gray };
Button button_Run2 = button_GenerateArray;
// list buttons
Button button_ListInsert = button_SelectionSort;
Button button_ListDeleteByValue = button_BubbleSort;

typedef struct Container{
  Rectangle rect;
} Container;

Container container_Operation = {0, 0, screenWidth, 70};
Container container_Action = {0, 70, 170, screenHeight};
Container container_Back = {0, 0, screenWidth, screenHeight};
Container container_TextInputBox = {170, 70, screenWidth - 330, 50};
Container container_TargetInputBox = {170, 130, 310, 50};
Container container_SortedArrayOutputLabelBox = {170, 130, screenWidth - 340, 50};
Container container_FoundTargetOutputLabelBox = {170, 190, screenWidth - 340, 50};
Container container_HashKeyInputField = {170, 70, 150, 50};
Container container_HashValueInputField = {container_HashKeyInputField.rect.x + 160, 70,  310, 50};
Container container_ListValueBox = container_SortedArrayOutputLabelBox;

void DrawThings(int selected[], Vector2 mouse);
void ButtonLogic(int selected[], Vector2 mouse);
vector<int> TextBox(Vector2 mouse);
void DoThing(void (*funcPtr)());
bool DrawButton(Button btn, Vector2 mouse, Color hoverColor, string text, bool isFocused);
bool CheckCollisionClick(Vector2 mouse, Button button);
bool CheckCollisionClick(Vector2 mouse, Container container);
bool GuiInputBox(Container bounds, string& buffer, bool& isFocused, string label);
void DrawValueBox(Container bounds, string label, vector<int>& data, Color themeColor, bool isPlaceholder=false);
vector<int> ParseStringToVector(string& input);
void DrawLabelBox(Container bounds, string label, Color themeColor);
void DrawList(Node* head, Vector2 startPos, Color themeColor);

void GUI() {

  InitWindow(screenWidth, screenHeight, "SSHub");
  SetTargetFPS(60);
  
  int selected[2]; 
  selected[0] = -1,
  selected[1] = -1;
  
  string input;
  while (!WindowShouldClose()) {

    Vector2 mouse = GetMousePosition();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // draw containers
    DrawRectangleRec(container_Back.rect, black2);
    DrawRectangleRec(container_Operation.rect, black);
    DrawRectangleRec(container_Action.rect, black);

    DrawThings(selected, mouse);
    ButtonLogic(selected, mouse);

    DrawText("Made by @JFenn28Uu", screenWidth-120, screenHeight-20, 10, black);

    EndDrawing();
  }

  CloseWindow();
}

void ButtonLogic(int selected[], Vector2 mouse){
  // Operation buttons logic
  if (CheckCollisionClick(mouse, button_Sorting)) {
      selected[0] = 0;
      selected[1] = -1;
  }
  if (CheckCollisionClick(mouse, button_Searching)) {
      selected[0] = 1;
      selected[1] = -1;
  }
  if (CheckCollisionClick(mouse, button_Hash)) {
      selected[0] = 2;
      selected[1] = -1;
  }
  if (CheckCollisionClick(mouse, button_Lists)) {
      selected[0] = 3;
      selected[1] = -1;
  }
  // Sorting action buttons logic
  if (selected[0] == 0){
    if (CheckCollisionClick(mouse, button_SelectionSort)) selected[1] = 0;
    if (CheckCollisionClick(mouse, button_BubbleSort)) selected[1] = 1;
    if (CheckCollisionClick(mouse, button_PasteSort)) selected[1] = 2;
    if (CheckCollisionClick(mouse, button_MergeSort)) selected[1] = 3;
    if (CheckCollisionClick(mouse, button_QuickSort)) selected[1] = 4;
    if (CheckCollisionClick(mouse, button_ShakerSort)) selected[1] = 5;
    if (CheckCollisionClick(mouse, button_ShellSort)) selected[1] = 6;
    if (CheckCollisionClick(mouse, button_HeapSort)) selected[1] = 7;
  }
  // Searching action buttons logic
  if (selected[0] == 1){
    if (CheckCollisionClick(mouse, button_LinearSearch)) selected[1] = 0;
    if (CheckCollisionClick(mouse, button_LinearSearchWithBarrier)) selected[1] = 1;
    if (CheckCollisionClick(mouse, button_BinarySearch)) selected[1] = 2;
  }
  // Hash action buttons logic
  if (selected[0] == 2){
    if (CheckCollisionClick(mouse, button_HashInsert)) selected[1] = 0;
    if (CheckCollisionClick(mouse, button_HashRemove)) selected[1] = 1;
    if (CheckCollisionClick(mouse, button_HashSearch)) selected[1] = 2;
  }
  if (selected[0] == 3){
    if (CheckCollisionClick(mouse, button_ListInsert)) selected[1] = 0;
    if (CheckCollisionClick(mouse, button_ListDeleteByValue)) selected[1] = 1;
  }
  // Actually coding actions

  // if (subSelected == 0 and pressedGenerateOrDoWorkButton) do SelectionSort
  // if (subSelected == 1 ...) ...

}

void DrawThings(int selected[], Vector2 mouse){
  // Draw operation buttons
  // i could pass here button parameters to draw and react. instead of making a ton of draws for button manually, 
  // i could pass structure element to function calland everything would`ve worked
  // maybe, void ButtonDraw(int selected[], char label[], struct button_Some)
  DrawButton(button_Sorting, mouse, selected[0] == 0 ? blue : gray, "Sorting", false);
  DrawButton(button_Searching, mouse, selected[0] == 1 ? blue : gray, "Searching", false);
  DrawButton(button_Hash, mouse, selected[0] == 2 ? blue : gray, "Hash", false);
  DrawButton(button_Lists, mouse, selected[0] == 3 ? blue : gray, "List", false);
  // Draw action buttons
  if (selected[0] == 0) {
    DrawButton(button_SelectionSort, mouse, selected[1] == 0 ? yellow : gray, "Selection", false);
    DrawButton(button_BubbleSort, mouse, selected[1] == 1 ? yellow : gray, "Bubble", false);
    DrawButton(button_PasteSort, mouse, selected[1] == 2 ? yellow : gray, "Paste", false);
    DrawButton(button_MergeSort, mouse, selected[1] == 3 ? yellow : gray, "Merge", false);
    DrawButton(button_QuickSort, mouse, selected[1] == 4 ? yellow : gray, "Quick", false);
    DrawButton(button_ShakerSort, mouse, selected[1] == 5 ? yellow : gray, "Shaker", false);
    DrawButton(button_ShellSort, mouse, selected[1] == 6 ? yellow : gray, "Shell", false);
    DrawButton(button_HeapSort, mouse, selected[1] == 7 ? yellow : gray, "Heap", false);
  }
  else if (selected[0] == 1) {
    DrawButton(button_LinearSearch, mouse, selected[1] == 0 ? yellow : gray, "Linear", false);
    DrawButton(button_LinearSearchWithBarrier, mouse, selected[1] == 1 ? yellow : gray, "Linear(barr)", false);
    DrawButton(button_BinarySearch, mouse, selected[1] == 2 ? yellow : gray, "Binary", false);
  }
  else if (selected[0] == 2) {
    DrawButton(button_HashInsert, mouse, selected[1] == 0 ? yellow : gray, "Insert", false);
    DrawButton(button_HashRemove, mouse, selected[1] == 1 ? yellow : gray, "Remove", false);
    DrawButton(button_HashSearch, mouse, selected[1] == 2 ? yellow : gray, "Search", false);
  }
  else if (selected[0] == 3) {
    DrawButton(button_ListInsert, mouse, selected[1] == 0 ? yellow : gray, "Insert", false);
    DrawButton(button_ListDeleteByValue, mouse, selected[1] == 1 ? yellow : gray, "Remove", false);
  }
  else selected[1] = -1;


  // draw text field if appropriate operations choosed
  if (selected[0] == 0 and selected[1] >= 0) {
    if (DrawButton(button_GenerateArray, mouse, yellow, "Generate", true)){
      parsedArray = ArrGenV();
    }
    DrawValueBox(container_TextInputBox, "", parsedArray, yellow, true);
    if(!sortedArray.empty()) DrawValueBox(container_SortedArrayOutputLabelBox, "", sortedArray, green);

    if (DrawButton(button_Run, mouse, yellow, "Run", true) && !parsedArray.empty()) {
      sortedArray = parsedArray;
      if (selected[1] == 0) SelectionSort(sortedArray, sortedArray.size());
      if (selected[1] == 1) BubbleSort(sortedArray, sortedArray.size());
      if (selected[1] == 2) PasteSort(sortedArray, sortedArray.size());
      if (selected[1] == 3) MergeSort(sortedArray, 0, sortedArray.size() - 1);
      if (selected[1] == 4) QuickSort(sortedArray, 0, sortedArray.size() - 1);
      if (selected[1] == 5) ShakerSort(sortedArray, sortedArray.size());
      if (selected[1] == 6) ShellSort(sortedArray, sortedArray.size());
      if (selected[1] == 7) HeapSort(sortedArray, sortedArray.size());
    }
  }
  if (selected[0] == 1 and selected[1] >= 0) {
    if (DrawButton(button_GenerateArray, mouse, yellow, "Generate", true)){
      parsedArray = ArrGenV();
      sortedArray = parsedArray;
      BubbleSort(sortedArray, parsedArray.size());
    }

    DrawValueBox(container_TextInputBox, "", sortedArray, yellow, true);

    if(GuiInputBox(container_TargetInputBox, stringSearchTarget, isTextFocused, "Enter target") and !stringSearchTarget.empty())
      searchTarget = stoi(stringSearchTarget);
      
    if(!parsedArray.empty())
      if(searchResult and newSearchTarget == searchTarget)
        DrawLabelBox(container_FoundTargetOutputLabelBox, CheckReturnToString(searchResult, searchTarget), green);

    if (DrawButton(button_Run, mouse, yellow, "Run", true) && !parsedArray.empty()) {
      newSearchTarget = searchTarget;
      if (selected[1] == 0) searchResult = LinearSearch(sortedArray, sortedArray.size(), searchTarget);
      if (selected[1] == 1) searchResult = LinearSearchWithBarrier(sortedArray, sortedArray.size(), searchTarget);
      if (selected[1] == 2) searchResult = BinarySearch(sortedArray, sortedArray.size(), searchTarget);
    }
  }
  if (selected[0] == 2 and selected[1] >= 0) {
    if(GuiInputBox(container_HashKeyInputField, hashKeyString, isKeyFieldFocused, "Key") and !hashKeyString.empty())
      hashKeyInput = stoi(hashKeyString);

    if(GuiInputBox(container_HashValueInputField, hashValueString, isValueFieldFocused, "Value") and !hashValueString.empty())
      hashValueInput = stoi(hashValueString);

    hashTable.Draw(170, 130, gray, yellow, green);
      
    if (DrawButton(button_Run2, mouse, yellow, "Run", true) and !hashKeyString.empty()) {
      if (selected[1] == 0) hashTable.Insert(hashKeyInput, hashValueInput);
      if (selected[1] == 1) hashTable.Remove(hashKeyInput);
      if (selected[1] == 2) CheckReturnToString(hashTable.SearchKey(hashKeyInput), hashKeyInput);
      hashValueString.erase();
      hashKeyString.erase();
    }
  }
  if (selected[0] == 3 and selected[1] >= 0) {
    if(GuiInputBox(container_TextInputBox, hashValueString, isValueFieldFocused, "Value") and !hashValueString.empty())
      hashValueInput = stoi(hashValueString);

    if(mylist != nullptr) DrawList(mylist, {170, 130}, gray);

    if (DrawButton(button_Run2, mouse, yellow, "Run", true) and !hashValueString.empty()) {
      if (selected[1] == 0) mylist = Insert(mylist, hashValueInput);
      if (selected[1] == 1) mylist = DeleteByValue(mylist, hashValueInput);
      hashValueString.erase();
    }
  }
}

void DoThing(void (*funcPtr)()){
  funcPtr();
}

bool DrawButton(Button btn, Vector2 mouse, Color hoverColor, string text, bool isFocused=false) {
  bool isHovered = CheckCollisionPointRec(mouse, btn.rect);
  if(isFocused) DrawRectangleRec(btn.rect, isHovered ? hoverColor : btn.color);
  else DrawRectangleRec(btn.rect, hoverColor); 
  
  DrawText(text.c_str(), btn.rect.x + gap, btn.rect.y + gap, 20, WHITE);
  return CheckCollisionClick(mouse, btn);
}

bool CheckCollisionClick(Vector2 mouse, Button button){
  return CheckCollisionPointRec(mouse, button.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool CheckCollisionClick(Vector2 mouse, Container container){
  return CheckCollisionPointRec(mouse, container.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void DrawValueBox(Container bounds, string label, vector<int>& data, Color themeColor, bool isPlaceholder) {
    DrawRectangleRec(bounds.rect, gray); 
    DrawRectangleLinesEx(bounds.rect, 2, themeColor);
    
    if(isPlaceholder and data.empty()) DrawText("Click \"Generate\"", bounds.rect.x + gap, bounds.rect.y + gap, 20, WHITE);
    string text = label;
    text += "";
    for (size_t i = 0; i < data.size(); i++) 
        text += to_string(data[i]) + (i == data.size() - 1 ? "" : " ");

    DrawText(text.c_str(), bounds.rect.x + gap, bounds.rect.y + gap, 20, WHITE);
}

void DrawLabelBox(Container bounds, string label, Color themeColor) {
    DrawRectangleRec(bounds.rect, gray); 
    DrawRectangleLinesEx(bounds.rect, 2, themeColor);
    DrawText(label.c_str(), bounds.rect.x + gap, bounds.rect.y + gap, 20, WHITE);
}

bool GuiInputBox(Container bounds, string& buffer, bool& isFocused, string label) {
    bool changed = false;
    Vector2 mouse = GetMousePosition();
    bool hovering = CheckCollisionPointRec(mouse, bounds.rect);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) isFocused = hovering;

    if (isFocused) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 48 && key <= 57) || key == 32 || key == 45) {
                buffer += (char)key;
                changed = true;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !buffer.empty()) {
            buffer.pop_back();
            changed = true;
        }
    } else {
        if (hovering) SetMouseCursor(MOUSE_CURSOR_IBEAM);
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    DrawRectangleRec(bounds.rect, gray); 
    DrawRectangleLinesEx(bounds.rect, 2, isFocused ? green : gray);

    if (buffer.empty() && !isFocused) {
        DrawText(label.c_str(), bounds.rect.x + gap, bounds.rect.y + gap, 20, yellow);
    } else {
        DrawText(buffer.c_str(), bounds.rect.x + gap, bounds.rect.y + gap, 20, WHITE);
    }

    if (isFocused) {
        int textWidth = MeasureText(buffer.c_str(), 20);
        DrawRectangle(bounds.rect.x + gap + textWidth, bounds.rect.y + gap, 2, 20, blue);
    }

    return changed;
}

vector<int> ParseStringToVector(string& input) {
    vector<int> result;
    auto split_view = input | views::split(' ');
    for (auto&& part : split_view) {
        string s(part.begin(), part.end());
        if (!s.empty() && s != "-") {
            try {
                result.push_back(stoi(s));
            } catch (...) { /* Skip invalid segments */ }
        }
    }
    return result;
}

void DrawList(Node* head, Vector2 startPos, Color themeColor) {
  Node* current = head;
  Vector2 cursor = startPos;
  int nodeWidth = 50,
    nodeHeight = 50,
    horizontalSpacing = 10;  
  while (current != nullptr) {
    string label = to_string(current->data);
    int nodeWidthT = max(nodeWidth, MeasureText(label.c_str(), 20) + (gap * 2));

    Rectangle rect = { cursor.x, cursor.y, (float)nodeWidthT, (float)nodeHeight };
    Container bounds = { rect }; 
    
    DrawLabelBox(bounds, label, themeColor);

    if (current->next != nullptr) {
      Vector2 startLine = { cursor.x + nodeWidthT, cursor.y + 15 };
      Vector2 endLine = { cursor.x + nodeWidthT + horizontalSpacing, cursor.y + 15 };
      DrawLineEx(startLine, endLine, 2, green);
      DrawTriangle({endLine.x, endLine.y}, {endLine.x - 5, endLine.y - 5}, {endLine.x - 5, endLine.y + 5}, green);

      Vector2 startPrev = { cursor.x + nodeWidthT + horizontalSpacing, cursor.y + 35 };
      Vector2 endPrev = { cursor.x + nodeWidthT, cursor.y + 35 };
      DrawLineEx(startPrev, endPrev, 2, yellow);
      DrawTriangle({endPrev.x, endPrev.y}, {endPrev.x + 5, endPrev.y + 5}, {endPrev.x + 5, endPrev.y - 5}, yellow);
    }

    cursor.x += (nodeWidthT + horizontalSpacing);
    current = current->next;
  }
}
