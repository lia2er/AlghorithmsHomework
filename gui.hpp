#include <iostream>
#include <raylib.h>
#include <string>
#include <ranges>
#include <vector>
#include "sorting.hpp"

using namespace std;

const int screenWidth = 800;
const int screenHeight = 720;
const int gap = 15;

const Color green = {0x98, 0x97, 0x1a, 255},
      yellow = {0xd7, 0x99, 0x21, 255},
      blue = {0x45, 0x85, 0x88, 255},
      black = {0x28, 0x28, 0x28, 255},
      black2 = {0x3c, 0x38, 0x36, 255},
      gray = {0x50, 0x49, 0x45, 255},
      red = {0xcc, 0x24, 0x1d, 255};


struct btn{
  // maybe i should remake it to vertical alignment
  Rectangle Sorting = { 10, 10, 150, 50 };
  Rectangle Searching = { 170, 10, 150, 50 };
  Rectangle Hash = { 330, 10, 150, 50 };
  Rectangle SelectionSort = {10, 70, 150, 50};
  Rectangle BubbleSort = {10, 130, 150, 50};
  Rectangle MergeSort = {10, 190, 150, 50};
  Rectangle PasteSort = {10, 250, 150, 50};
  Rectangle QuickSort = {10, 310, 150, 50};
  Rectangle ShellSort = {10, 370, 150, 50};
  Rectangle ShakerSort = {10, 430, 150, 50};
  Rectangle HeapSort = {10, 490, 150, 50};
  Rectangle Back = {};
  Rectangle GenerateArray = {};
  Rectangle DoIt = {HeapSort.x, HeapSort.y + gap, HeapSort.width, HeapSort.height};
} btn;

struct cntr{
  Rectangle Operation = { 0, 0, screenWidth, 70};
  Rectangle Action = { 0, 70, 170, screenHeight};
  Rectangle Back = {170, 70, screenWidth, screenHeight};
  Rectangle TextBox = {190, 90, 400, 50};
} cntr;

void ButtonDraw(int selected[]);
void ButtonLogic(int selected[], Vector2 mouse);
vector<int> TextBox(Vector2 mouse);

void GUI() {

  InitWindow(screenWidth, screenHeight, "SSHub");
  SetTargetFPS(60);
  
  int selected[2]; 
  selected[0] = -1,
  selected[1] = -1;
  
  string input;
  vector<int> output;
  while (!WindowShouldClose()) {
    Vector2 mouse = GetMousePosition();
    ButtonLogic(selected, mouse);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // draw containers
    DrawRectangleRec(cntr.Operation, black);
    DrawRectangleRec(cntr.Action, black);
    DrawRectangleRec(cntr.Back, black2);

    ButtonDraw(selected);

    output = TextBox(mouse);

    EndDrawing();
  }

  CloseWindow();
  size_t size = output.size();
  cout << size << endl;
  BubbleSort(output, size);
}

void ButtonLogic(int selected[], Vector2 mouse){
  // Operation buttons logic
  if (CheckCollisionPointRec(mouse, btn.Sorting) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[0] = 0;
  if (CheckCollisionPointRec(mouse, btn.Searching) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[0] = 1;
  if (CheckCollisionPointRec(mouse, btn.Hash) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[0] = 2;
  // Action buttons logic
  if (CheckCollisionPointRec(mouse, btn.SelectionSort) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 0;
  if (CheckCollisionPointRec(mouse, btn.BubbleSort) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 1;
  if (CheckCollisionPointRec(mouse, btn.PasteSort) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 2;
  if (CheckCollisionPointRec(mouse, btn.MergeSort) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 3;
  if (CheckCollisionPointRec(mouse, btn.QuickSort) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 4;
  if (CheckCollisionPointRec(mouse, btn.ShakerSort) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 5;
  if (CheckCollisionPointRec(mouse, btn.ShellSort) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 6;
  if (CheckCollisionPointRec(mouse, btn.HeapSort) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 7;
  
  // Actually coding actions
  if (selected[0] == 0 and selected[1] == 0){}
  // if (subSelected == 0 and pressedGenerateOrDoWorkButton) do SelectionSort
  // if (subSelected == 1 ...) ...

}

void ButtonDraw(int selected[]){
  // Draw operation buttons
  // i could pass here button parameters to draw and react. instead of making a ton of draws for button manually, 
  // i could pass structure element to function calland everything would`ve worked
  // maybe, void ButtonDraw(int selected[], char label[], struct btn.Some)
	DrawRectangleRec(btn.Sorting, selected[0] == 0 ? blue : gray);
  DrawRectangleRec(btn.Searching, selected[0] == 1 ? blue : gray);
  DrawRectangleRec(btn.Hash, selected[0] == 2 ? blue : gray);

  DrawText("Sorting", btn.Sorting.x + gap, btn.Sorting.y + gap, 20, WHITE);
  DrawText("Searching", btn.Searching.x + gap, btn.Searching.y + gap, 20, WHITE);
  DrawText("Hash Table", btn.Hash.x + gap, btn.Hash.y + gap, 20, WHITE);
  // Draw action buttons
  if (selected[0] == 0) {
    DrawRectangleRec(btn.SelectionSort, selected[1] == 0 ? yellow : gray);
    DrawRectangleRec(btn.BubbleSort, selected[1] == 1 ? yellow : gray);
    DrawRectangleRec(btn.PasteSort, selected[1] == 2 ? yellow : gray);
    DrawRectangleRec(btn.MergeSort, selected[1] == 3 ? yellow : gray);
    DrawRectangleRec(btn.QuickSort, selected[1] == 4 ? yellow : gray);
    DrawRectangleRec(btn.ShakerSort, selected[1] == 5 ? yellow : gray);
    DrawRectangleRec(btn.ShellSort, selected[1] == 6 ? yellow : gray);
    DrawRectangleRec(btn.HeapSort, selected[1] == 7 ? yellow : gray);

    DrawText("Selection", btn.SelectionSort.x + gap, btn.SelectionSort.y + gap, 20, WHITE);
    DrawText("Bubble", btn.BubbleSort.x + gap, btn.BubbleSort.y + gap, 20, WHITE);
    DrawText("Paste", btn.PasteSort.x + gap, btn.PasteSort.y + gap, 20, WHITE);
    DrawText("Merge", btn.MergeSort.x + gap, btn.MergeSort.y + gap, 20, WHITE);
    DrawText("Quick", btn.QuickSort.x + gap, btn.QuickSort.y + gap, 20, WHITE);
    DrawText("Shaker", btn.ShakerSort.x + gap, btn.ShakerSort.y + gap, 20, WHITE);
    DrawText("Shell", btn.ShellSort.x + gap, btn.ShellSort.y + gap, 20, WHITE);
    DrawText("Heap", btn.HeapSort.x + gap, btn.HeapSort.y + gap, 20, WHITE);
  }
  else if (selected[0] == 1) {}
  else if (selected[0] == 2) {}
  else selected[1] = -1;
}

void DoThing(void (*funcPtr)()){
  funcPtr();
}

vector<int> TextBox(Vector2 mouse) {
  vector<int> output;
  static string input = ""; 
  static int framesCounter = 0;
  static bool isFocused = false;

  // 1. Handle Focusing
  if (CheckCollisionPointRec(mouse, cntr.TextBox)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) isFocused = true;
  } else {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) isFocused = false;
  }

  if (isFocused) {
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    
    int key = GetCharPressed();
    while (key > 0) {
      if ((key >= 48) and (key <= 57) or (key == 32)) input += (char)key;
      key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) and !input.empty()) {
      input.pop_back();
    }
    framesCounter++;
  } else {
    if (!CheckCollisionPointRec(mouse, cntr.TextBox)) {
      SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    framesCounter = 0;
  }

  DrawRectangleRec(cntr.TextBox, gray);
  
  Color borderColor = (isFocused or CheckCollisionPointRec(mouse, cntr.TextBox)) ? green : red;
  DrawRectangleLinesEx(cntr.TextBox, 2, borderColor);

  DrawText(input.c_str(), (int)cntr.TextBox.x + 5, (int)cntr.TextBox.y + 8, 20, WHITE);

  if (isFocused && (framesCounter / 20) % 2 == 0) {
    int textWidth = MeasureText(input.c_str(), 20);
    DrawRectangle(cntr.TextBox.x + 8 + textWidth, cntr.TextBox.y + 8, 2, 18, red);
  }

  if(!isFocused) {
    int i;
    auto split_view = input | views::split(' ');
    for(auto&& part: split_view){
      if(part.empty()) continue;
      output.push_back(std::stoi(std::string(part.begin(), part.end())));
    }
  }
  return output;
}
