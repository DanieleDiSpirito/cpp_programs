#include <raylib.h>
#include "game.cpp"
#include "constant.hpp"

using namespace std;
using namespace Constant;

double lastUpdateTime = 0;

bool eventTriggered(double interval) {
    double currTime = GetTime();
    if(currTime - lastUpdateTime >= interval) {
        lastUpdateTime = currTime;
        return true;
    }
    return false;
}

int main() {
    InitWindow(CELL_SIZE*CELL_COUNT, CELL_SIZE*CELL_COUNT, "Snake");
    SetTargetFPS(FPS);

    Game game = Game();

    while (!WindowShouldClose()) {
        BeginDrawing();

        if(eventTriggered(game.getInterval())) {
            game.Update();
        }

        if((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game.snake.getDir().y != 1) {
            game.snake.setDir({0, -1});
            if(!game.isRunning()) game.Restart();
        } else if((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && game.snake.getDir().y != -1) {
            game.snake.setDir({0, 1});
            if(!game.isRunning()) game.Restart();
        } else if((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && game.snake.getDir().x != 1) {
            game.snake.setDir({-1, 0});
            if(!game.isRunning()) game.Restart();
        } else if((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && game.snake.getDir().x != -1) {
            game.snake.setDir({1, 0});
            if(!game.isRunning()) game.Restart();
        }

        ClearBackground(gray);
        DrawText(TextFormat("%i", game.getScore()), 5, 5, 30, WHITE);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}