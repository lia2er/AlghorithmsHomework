#include <iostream>
#include <raylib.h>
#include <string>
#include <ranges>
#include <vector>
#include "sorting.hpp"
#include "search.hpp"
#include "utility.hpp"

using namespace std;

const int screenWidth = 800;
const int screenHeight = 720;
const int gap = 15;
vector<int> output;

const Color green = {0x98, 0x97, 0x1a, 255},
      yellow = {0xd7, 0x99, 0x21, 255},
      blue = {0x45, 0x85, 0x88, 255},
      black = {0x28, 0x28, 0x28, 255},
      black2 = {0x3c, 0x38, 0x36, 255},
      gray = {0x50, 0x49, 0x45, 255},
      red = {0xcc, 0x24, 0x1d, 255};

/*
struct btn{
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
} btn;*/

typedef struct Button {
    Rectangle rect;
    Color color;
} Button;

// One-line initializations: { {x, y, width, height}, color }
Button button_Sorting       = { { 10, 10, 150, 50 }, gray };
Button button_Searching     = { { 170, 10, 150, 50 }, gray };
Button button_Hash          = { { 330, 10, 150, 50 }, gray };
Button button_SelectionSort = { { 10, 70, 150, 50 }, gray };
Button button_BubbleSort    = { { 10, 130, 150, 50 }, gray };
Button button_MergeSort     = { { 10, 190, 150, 50 }, gray };
Button button_PasteSort     = { { 10, 250, 150, 50 }, gray };
Button button_QuickSort     = { { 10, 310, 150, 50 }, gray };
Button button_ShellSort     = { { 10, 370, 150, 50 }, gray };
Button button_ShakerSort    = { { 10, 430, 150, 50 }, gray };
Button button_HeapSort      = { { 10, 490, 150, 50 }, gray };
Button button_Back          = { { 0, 0, 0, 0 }, gray }; 
Button button_GenerateArray = { { screenWidth - 160, 70, 150, 50 }, gray };
Button button_DoIt          = { { button_HeapSort.rect.x, button_HeapSort.rect.y + gap, button_HeapSort.rect.width, button_HeapSort.rect.height }, gray };


struct cntr{
  Rectangle Operation = { 0, 0, screenWidth, 70};
  Rectangle Action = { 0, 70, 170, screenHeight};
  Rectangle Back = {170, 70, screenWidth, screenHeight};
  Rectangle TextBox = {170, 70, screenWidth - 340, 50};
} cntr;

void DrawThings(int selected[], Vector2 mouse);
void ButtonLogic(int selected[], Vector2 mouse);
vector<int> TextBox(Vector2 mouse);
void DoThing(void (*funcPtr)());
bool DrawButton(Button btn, Vector2 mouse, Color hoverColor, string text, bool isFocused);

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
    DrawRectangleRec(cntr.Operation, black);
    DrawRectangleRec(cntr.Action, black);
    DrawRectangleRec(cntr.Back, black2);

    DrawThings(selected, mouse);
    ButtonLogic(selected, mouse);

    EndDrawing();
  }

  CloseWindow();
}

void ButtonLogic(int selected[], Vector2 mouse){
  // Operation buttons logic
  if (CheckCollisionPointRec(mouse, button_Sorting.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    selected[0] = 0;
    selected[1] = -1;
  }
  if (CheckCollisionPointRec(mouse, button_Searching.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    selected[0] = 1;
    selected[1] = -1;
  }
  if (CheckCollisionPointRec(mouse, button_Hash.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    selected[0] = 2;
    selected[1] = -1;
  }
  // Action buttons logic
  if (CheckCollisionPointRec(mouse, button_SelectionSort.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 0;
  if (CheckCollisionPointRec(mouse, button_BubbleSort.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 1;
  if (CheckCollisionPointRec(mouse, button_PasteSort.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 2;
  if (CheckCollisionPointRec(mouse, button_MergeSort.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 3;
  if (CheckCollisionPointRec(mouse, button_QuickSort.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 4;
  if (CheckCollisionPointRec(mouse, button_ShakerSort.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 5;
  if (CheckCollisionPointRec(mouse, button_ShellSort.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 6;
  if (CheckCollisionPointRec(mouse, button_HeapSort.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    selected[1] = 7;
  
  // Actually coding actions
  if (selected[0] == 0 and selected[1] == 0){}
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
  else if (selected[0] == 1) {}
  else if (selected[0] == 2) {}
  else selected[1] = -1;


  // draw text field if appropriate operations choosed
  if ((selected[0] == 0 or selected[0] == 1) and selected[1] >= 0) {
    output = TextBox(mouse);
    bool isGeneratePressed = DrawButton(button_GenerateArray, mouse, yellow, "Generate", false);
  }
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
      if ((key >= 48) and (key <= 57) or (key == 32) or (key == 45)) input += (char)key;
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
  
  Color borderColor = (isFocused or CheckCollisionPointRec(mouse, cntr.TextBox)) ? green : gray;
  DrawRectangleLinesEx(cntr.TextBox, 2, borderColor);

  DrawText(input.c_str(), cntr.TextBox.x + gap, cntr.TextBox.y + gap, 20, WHITE);
  if(input.empty()) DrawText("Input array here... or click \"Generate\"", cntr.TextBox.x + gap, cntr.TextBox.y + gap, 20, WHITE);

  if (isFocused && (framesCounter / 20) % 2 == 0) {
    int textWidth = MeasureText(input.c_str(), 20);
    DrawRectangle(cntr.TextBox.x + gap + textWidth, cntr.TextBox.y + gap, 2, 18, red);
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

bool DrawButton(Button btn, Vector2 mouse, Color hoverColor, string text, bool isFocused=false) {
  if(isFocused)
    DrawRectangleRec(btn.rect, CheckCollisionPointRec(mouse, btn.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)? hoverColor : btn.color);
  else DrawRectangleRec(btn.rect, hoverColor);
  DrawText(text.c_str(), btn.rect.x + gap, btn.rect.y + gap, 20, WHITE);
  if(CheckCollisionPointRec(mouse, btn.rect) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return true;
  else return false;
}

