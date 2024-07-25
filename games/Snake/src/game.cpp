#include <raylib.h>
#include "snake.cpp"
#include "food.cpp"
#include "constant.hpp"

using namespace Constant;

class Game {
    private:
        bool running = true;
        float interval = SPEED;
        int score = 0;
    public:
        Snake snake = Snake();
        Food apple = Food(snake.body);

        Game() {}

        void Draw() {
            snake.Draw();
            apple.Draw();
        }

        int getScore() { return score; }

        float getInterval() { return interval; }

        void speedUp() { interval = max(0.03, interval * 0.8); }

        bool isRunning() { return running; }

        void Restart() { running = true; }

        void End() {
            snake = Snake();
            apple.setPosition(apple.GenerateRandomPos(snake.body));
            interval = 0.1;
            score = 0;
            running = false;
        }

        void Update() {
            if(running) {
                snake.Update();
                checkCollissionWithFood();
                checkCollissionWithItself();
            }
        }

        void checkCollissionWithFood() {
            if(Vector2Equals(snake.body[0], apple.getPosition())) {
                apple.setPosition(apple.GenerateRandomPos(snake.body));
                speedUp();
                score++;
                snake.addSegment = true;
            }
        }

        void checkCollissionWithItself() {
            if(snake.ElementInDeque(snake.body[0], snake.body)) {
                End();
            }
        }
};