#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_LEN 100

int gameOver;
int score;
int dir;
int snakeLen;
int foodX, foodY;
int tailX[MAX_LEN], tailY[MAX_LEN];
int headX, headY;

void setup() {
    gameOver = 0;
    score = 0;
    dir = 1;
    snakeLen = 1;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    tailX[0] = headX;
    tailY[0] = headY;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void draw() {
    printf("\033[2J\033[H");
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0) printf("#");
            int printed = 0;
            if (x == headX && y == headY) {
                printf("O");
                printed = 1;
            } else if (x == foodX && y == foodY) {
                printf("F");
                printed = 1;
            } else {
                for (int k = 0; k < snakeLen; k++) {
                    if (tailX[k] == x && tailY[k] == y) {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }
            }
            if (!printed) printf(" ");
            if (x == WIDTH - 1) printf("#");
        }
        printf("\n");
    }
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\nScore: %d\n", score);
    printf("Press 'x' to quit.\n");
}

void input() {
    char key;
    if (scanf(" %c", &key) == 1) {
        if (key == 'a' && dir != 1) dir = 0;
        else if (key == 'd' && dir != 0) dir = 1;
        else if (key == 'w' && dir != 3) dir = 2;
        else if (key == 's' && dir != 2) dir = 3;
        else if (key == 'x') gameOver = 1;
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;
    for (int i = 1; i < snakeLen; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    if (dir == 0) headX--;
    else if (dir == 1) headX++;
    else if (dir == 2) headY--;
    else if (dir == 3) headY++;
    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) gameOver = 1;
    for (int i = 0; i < snakeLen; i++) {
        if (tailX[i] == headX && tailY[i] == headY) gameOver = 1;
    }
    if (headX == foodX && headY == foodY) {
        score += 10;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        snakeLen++;
    }
}

int main() {
    srand(time(0));
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
    }
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
