#include "raylib.h"

// IMPORTANT: Define implementation in exactly ONE source file. [1](https://github.com/raysan5/raygui)[2](https://deepwiki.com/raysan5/raygui/2-getting-started)
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


int main()
{
    const int screenWidth = 900;
    const int screenHeight = 520;

    InitWindow(screenWidth, screenHeight, "raylib + raygui (C++ sample)");
    SetTargetFPS(60);

    // UI state
    bool showDemoPanel = true;
    bool checkValue = false;
    float sliderValue = 0.35f;

    // TextBox buffer (raygui expects mutable char buffer)
    char nameBuf[64] = "Arsen";
    bool nameEditMode = false;

    bool showModal = false;
    int modalResult = -1;

    while (!WindowShouldClose())
    {
        // ---- Drawing ----
        BeginDrawing();

        // raygui often uses its background color style; this matches raygui examples. [1](https://github.com/raysan5/raygui)
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // Top bar / title
        DrawText("raylib + raygui sample", 20, 16, 24, DARKBLUE);

        // A simple panel-like area
        if (showDemoPanel)
        {
            Rectangle panel = { 20, 60, 420, 420 };
            GuiPanel(panel, "Controls");

            // Button
            if (GuiButton({ 40, 100, 160, 32 }, "Show modal"))
            {
                showModal = true;
                modalResult = -1;
            }

            // Checkbox
            GuiCheckBox({ 40, 150, 20, 20 }, "Enable option", &checkValue);

            // Slider
            GuiLabel({ 40, 195, 140, 20 }, "Volume");
            GuiSlider({ 40, 220, 260, 20 }, "0", "100", &sliderValue, 0.0f, 1.0f);

            // TextBox (toggle edit mode with click)
            GuiLabel({ 40, 260, 140, 20 }, "Name");
            if (GuiTextBox({ 40, 285, 260, 32 }, nameBuf, 64, nameEditMode))
            {
                // In raygui, TextBox returns true when pressed; commonly used to toggle edit mode.
                nameEditMode = !nameEditMode;
            }

            // Some info text
            GuiLabel({ 40, 340, 360, 20 }, TextFormat("checkValue: %s", checkValue ? "true" : "false"));
            GuiLabel({ 40, 365, 360, 20 }, TextFormat("sliderValue: %.2f", sliderValue));
            GuiLabel({ 40, 390, 360, 20 }, TextFormat("name: %s", nameBuf));
        }

        // A “side” window area
        Rectangle side = { 470, 60, 410, 420 };
        GuiPanel(side, "Status");
        DrawText("Press ESC to exit.", 490, 110, 20, GRAY);
        DrawFPS(490, 140);

        // Modal message box (blocks interaction conceptually)
        if (showModal)
        {
            Rectangle box = { 250, 180, 400, 160 };
            modalResult = GuiMessageBox(
                box,
                "Confirm",
                "Do you like raygui?",
                "Yes;No"
            );

            // GuiMessageBox returns:
            // 0 = closed (or no selection), 1 = first button, 2 = second button (commonly)
            if (modalResult == 1 || modalResult == 2)
                showModal = false;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
