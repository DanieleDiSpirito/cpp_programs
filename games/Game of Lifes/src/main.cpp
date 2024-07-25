#include <raylib.h>
#include "simulation.hpp"

#define CELL_SIZE 5

int main() {
    int FPS = 12;
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(FPS);

    Simulation simulation{screenWidth, screenHeight, CELL_SIZE};
    
    while (!WindowShouldClose()) {
        // Updating
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            simulation.ToggleCell(row, column);
        }
        
        if(IsKeyPressed(KEY_ENTER)) {
            simulation.Start();
        } else if(IsKeyPressed(KEY_SPACE)) {
            simulation.Stop();
        } else if(IsKeyPressed(KEY_F)) {
            FPS += 2;
            SetTargetFPS(FPS);
        } else if(IsKeyPressed(KEY_S)) {
            FPS = (FPS >= 4) ? FPS - 2 : FPS;
            SetTargetFPS(FPS);
        } else if(IsKeyPressed(KEY_R)) {
            simulation.CreateRandomState();
        } else if(IsKeyPressed(KEY_C)) {
            simulation.ClearGrid();
        }

        if(simulation.isRunning()) simulation.Update();
        // Draw
        BeginDrawing();
        ClearBackground({20, 20, 20, 255});
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}