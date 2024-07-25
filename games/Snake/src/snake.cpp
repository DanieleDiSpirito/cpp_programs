#include <raylib.h>
#include <raymath.h>
#include <deque>
#include "constant.hpp"

using namespace Constant;

class Snake {
    private:
        Vector2 dir = {1, 0};
    public:
        std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        bool addSegment = false;

        Snake() {}

        void Draw() {
            for(auto b: body) {
                float x = b.x;
                float y = b.y;
                Rectangle rect = Rectangle{x * CELL_SIZE, y * CELL_SIZE, (float) CELL_SIZE, (float) CELL_SIZE};
                DrawRectangleRounded(rect, 0.5, 4, DARKGREEN);
            }
        }

        int Mod(int N, int D) {
            return (N % D >= 0) ? N % D : (N % D) + D;
        }

        Vector2 Vector2AddWithMod(Vector2 vec1, Vector2 vec2, int M) {
            int resX = Mod((int) vec1.x + (int) vec2.x, M);
            int resY = Mod((int) vec1.y + (int) vec2.y, M);
            return (Vector2) {(float) resX, (float) resY};
        }

        bool ElementInDeque(Vector2 el, std::deque<Vector2> deq) {
            for(unsigned int i = 1; i < deq.size(); i++) {
                if(Vector2Equals(el, deq[i])) return true;
            }
            return false;
        }

        void Update() {
            if(addSegment) {
                addSegment = false;
            } else {
                body.pop_back();
            }
            body.push_front(Vector2AddWithMod(body[0], dir, CELL_COUNT));
        }

        Vector2 getDir() { return dir; }

        void setDir(int x, int y) {
            dir = {(float) x, (float) y};
        }

        void setDir(Vector2 newDir) {
            dir = newDir;
        }
};