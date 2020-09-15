#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 50
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void init();
void show();
void updateWithInput();
void updateWithoutInput();
void gotoxy(int x, int y);
void hide();

int canvas[HEIGHT][WIDTH] = {0}; // -2 food; -1 wall; 0 space; 1 head; >1 body;
int direction;
int food_x, food_y;
int score;

int main(void)
{
    init();
    while (1)
    {
        show();
        updateWithInput();
        updateWithoutInput();
    }
    return 0;
}

void init()
{
    srand(time(NULL));
    for (int i = 0; i < HEIGHT; ++i)
    {
        canvas[i][0] = -1;
        canvas[i][WIDTH - 1] = -1;
    }
    for (int i = 0; i < WIDTH; ++i)
    {
        canvas[0][i] = -1;
        canvas[HEIGHT - 1][i] = -1;
    }
    score = 0;
    direction = RIGHT;
    canvas[HEIGHT / 2][WIDTH / 2] = 1;
    for (int i = 1; i < 4; ++i)
    {
        canvas[HEIGHT / 2][WIDTH / 2 - i] = i + 1;
    }
    food_y = rand() % (HEIGHT - 2) + 1;
    food_x = rand() % (WIDTH - 2) + 1;
    canvas[food_y][food_x] = -2;
    hide();
}

void show()
{
    gotoxy(0, 0);
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (canvas[i][j] == 0)
            {
                printf(" ");
            }
            else if (canvas[i][j] == -1)
            {
                printf("+");
            }
            else if (canvas[i][j] == 1)
            {
                printf("@");
            }
            else if (canvas[i][j] > 1)
            {
                printf("*");
            }
            else if (canvas[i][j] == -2)
            {
                printf("$");
            }
        }
        printf("\n");
    }
    printf("Move: W S A D\n");
    printf("Score: %d\n", score);
    Sleep(500 / (score + 1));
}

void updateWithInput()
{
    char input;

    if (kbhit())
    {
        input = getch();
        if (direction != DOWN)
        {
            if (input == 'w' || input == 'W')
            {
                direction = UP;
            }
        }
        if (direction != UP)
        {
            if (input == 's' || input == 'S')
            {
                direction = DOWN;
            }
        }
        if (direction != RIGHT)
        {
            if (input == 'a' || input == 'A')
            {
                direction = LEFT;
            }
        }
        if (direction != LEFT)
        {
            if (input == 'd' || input == 'D')
            {
                direction = RIGHT;
            }
        }
    }
}

void updateWithoutInput()
{
    int max = 0, oldTail_i, oldTail_j, oldHead_i, oldHead_j, newHead_i, newHead_j;
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (canvas[i][j] > 0)
            {
                canvas[i][j]++;
                if (max < canvas[i][j])
                {
                    max = canvas[i][j];
                    oldTail_i = i;
                    oldTail_j = j;
                }
                if (canvas[i][j] == 2)
                {
                    oldHead_i = i;
                    oldHead_j = j;
                }
            }
        }
    }
    if (direction == UP)
    {
        newHead_i = oldHead_i - 1;
        newHead_j = oldHead_j;
    }
    if (direction == DOWN)
    {
        newHead_i = oldHead_i + 1;
        newHead_j = oldHead_j;
    }
    if (direction == LEFT)
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j - 1;
    }
    if (direction == RIGHT)
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j + 1;
    }

    if (canvas[newHead_i][newHead_j] == -2)
    {
        canvas[food_y][food_x] = 0;
        food_y = rand() % (HEIGHT - 2) + 1;
        food_x = rand() % (WIDTH - 2) + 1;
        while (canvas[food_y][food_x] > 0)
        {
            food_y = rand() % (HEIGHT - 2) + 1;
            food_x = rand() % (WIDTH - 2) + 1;
        }
        canvas[food_y][food_x] = -2;
        score++;
    }
    else
    {
        canvas[oldTail_i][oldTail_j] = 0;
    }

    if (canvas[newHead_i][newHead_j] > 0 || canvas[newHead_i][newHead_j] == -1)
    {
        printf(">_<\npress ENTER to exit...");
        getchar();
        exit(0);
    }
    else
    {
        canvas[newHead_i][newHead_j] = 1;
    }
}

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void hide()
{
    CONSOLE_CURSOR_INFO cursor = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
