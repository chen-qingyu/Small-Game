#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define N 5

void init();
void show();
void updateWithInput();
void updateWithoutInput();
void gotoxy(int x, int y);
void hide();

int height, width;
int man_x, man_y;
int monster_x[N], monster_y[N];
clock_t start, end;

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
    width = 40;
    height = 20;
    man_x = width / 2;
    man_y = height / 2;
    for (int i = 0; i < N; ++i)
    {
        monster_x[i] = rand() % width;
        monster_y[i] = rand() % height;
    }
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
    printf("Move: W S A D; Try to hold on for 20 seconds.\n");
    start = clock();
}

void show()
{
    gotoxy(0, 0);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if ((i == man_y) && (j == man_x))
            {
                printf("*");
            }
            else if ((i == monster_y[0]) && (j == monster_x[0]))
            {
                printf("!");
            }
            else if ((i == monster_y[1]) && (j == monster_x[1]))
            {
                printf("!");
            }
            else if ((i == monster_y[2]) && (j == monster_x[2]))
            {
                printf("!");
            }
            else if ((i == monster_y[3]) && (j == monster_x[3]))
            {
                printf("!");
            }
            else if ((i == monster_y[4]) && (j == monster_x[4]))
            {
                printf("!");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    end = clock();
    printf("\n\nTime: %.2lf s\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void updateWithInput()
{
    char input;

    if (kbhit())
    {
        input = getch();

        if (man_y != 0)
        {
            if (input == 'w' || input == 'W')
            {
                man_y--;
            }
        }
        if (man_y != height - 1)
        {
            if (input == 's' || input == 'S')
            {
                man_y++;
            }
        }
        if (man_x != 0)
        {
            if (input == 'a' || input == 'A')
            {
                man_x--;
            }
        }
        if (man_x != width - 1)
        {
            if (input == 'd' || input == 'D')
            {
                man_x++;
            }
        }
    }
}

void updateWithoutInput()
{
    for (int i = 0; i < N; ++i)
    {
        if ((man_x == monster_x[i]) && (man_y == monster_y[i]))
        {
            if ((double)(end - start) / CLOCKS_PER_SEC > 20)
            {
                printf("\nYou're tooooooooo agile!\n");
                getchar();
                exit(0);
            }
            else
            {
                printf("\n>_<\npress ENTER to exit...");
                getchar();
                exit(0);
            }
        }
    }

    static int speed = 0;
    if (speed < 20 - (end - start) / CLOCKS_PER_SEC)
    {
        speed++;
    }
    if (speed >= 20 - (end - start) / CLOCKS_PER_SEC)
    {
        for (int i = 0; i < N; ++i)
        {
            if (monster_x[i] < man_x)
            {
                monster_x[i]++;
            }
            if (monster_x[i] > man_x)
            {
                monster_x[i]--;
            }
            if (monster_y[i] < man_y)
            {
                monster_y[i]++;
            }
            if (monster_y[i] > man_y)
            {
                monster_y[i]--;
            }
        }
        speed = 0;
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
