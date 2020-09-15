#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void init();
void show();
void updateWithInput();
void updateWithoutInput();
void gotoxy(int x, int y);
void hide();

int height, width;
int ball_x, ball_y;
int v_x, v_y;
int position_x, position_y, radius, left, right;
int money_x;
int score, money;

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
    height = 18;
    width = 25;
    ball_x = width / 2;
    ball_y = 1;
    v_x = 1;
    v_y = 1;
    position_y = height;
    position_x = width / 2;
    radius = 4;
    left = position_x - radius;
    right = position_x + radius;
    score = 0;
    money_x = width / 2;
    money = 0;
    hide();
    for (int i = 0; i <= height; ++i)
    {
        for (int j = 0; j <= width; ++j)
        {
            if ((i == height) || (j == width))
            {
                printf("+");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Move: A D\n");
}

void show()
{
    gotoxy(0, 0);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if ((i == ball_y) && (j == ball_x))
            {
                printf("o");
            }
            else if ((i == 0) && (j >= money_x - 1) && (j <= money_x + 1))
            {
                printf("$");
            }
            else if ((i == height - 1) && (j >= left) && (j <= right))
            {
                printf("=");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n\nScore: %d\nMoney: $ %d", score, money);
}

void updateWithInput()
{
    char input;

    if (kbhit())
    {
        input = getch();

        if (position_x != 0)
        {
            if (input == 'a' || input == 'A')
            {
                position_x--;
            }
        }
        if (position_x != width - 1)
        {
            if (input == 'd' || input == 'D')
            {
                position_x++;
            }
        }
    }
    Sleep(80);
}

void updateWithoutInput()
{
    left = position_x - radius;
    right = position_x + radius;

    if (ball_y == height - 2)
    {
        if ((ball_x >= left) && (ball_x <= right))
        {
            score++;
            v_y = -v_y;
        }
        else
        {
            printf("\n>_<\npress ENTER to exit...");
            getchar();
            exit(0);
        }
    }

    if ((ball_y == 0) && (ball_x >= money_x - 1) && (ball_x <= money_x + 1))
    {
        printf("\a");
        money += 3;
        money_x = rand() % width;
    }

    ball_x += v_x;
    ball_y += v_y;

    if ((ball_y == 0))
    {
        v_y = -v_y;
    }
    if ((ball_x == 0) || (ball_x == width - 1))
    {
        v_x = -v_x;
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
