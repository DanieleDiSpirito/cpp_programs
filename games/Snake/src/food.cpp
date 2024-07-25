#include <raylib.h>
#include <raymath.h>
#include <deque>
#include "constant.hpp"

using namespace Constant;
using namespace std;

class Food {
    private:
        Vector2 position;
        int cellSize;
        Texture2D texture;
    public:
        Food(deque<Vector2> snakeBody) {
            Image image = LoadImage("images/apple.png");
            ImageResize(&image, CELL_SIZE, CELL_SIZE);
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
            position = GenerateRandomPos(snakeBody);
            cellSize = CELL_SIZE;
        }

        ~Food() { // deconstructor
            UnloadTexture(texture);
        }

        void Draw() {
            DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
        }

        bool ElementInDeque(Vector2 el, deque<Vector2> deq) {
            for(Vector2 d: deq) {
                if(Vector2Equals(el, d)) return true;
            }
            return false;
        }

        Vector2 GeneretaRandomCell() {
            float x = GetRandomValue(0, CELL_COUNT - 1);
            float y = GetRandomValue(0, CELL_COUNT - 1);
            return (Vector2) {x, y};
        }

        Vector2 GenerateRandomPos(deque<Vector2> snakeBody) {
            Vector2 res;
            do {
                res = GeneretaRandomCell();
            } while(ElementInDeque(res, snakeBody));
            return res;
        }

        Vector2 getPosition() {
            return position;
        }
        
        void setPosition(Vector2 newPos) {
            position = newPos;
        }
};