// around 3 lives: live
// around 2 lives: hold
// others: die

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define HEIGHT 25
#define WIDTH 50

void init();
void show();
void updateWithInput();
void updateWithoutInput();
void gotoxy(int x, int y);
void hide();

int cells[HEIGHT][WIDTH];

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
        for (int j = 0; j < WIDTH; ++j)
        {
            cells[i][j] = rand() % 2; // or cells[i][j] = 1;
        }
        printf("\n");
    }
    printf("Just look.\n");
    hide();
}

void show()
{
    gotoxy(0, 0);
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (cells[i][j] == 1)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void updateWithInput()
{
}

void updateWithoutInput()
{
    int tmp[HEIGHT][WIDTH];
    int i, j, adjacent = 0;
    for (i = 0; i < HEIGHT; ++i)
    {
        for (j = 0; j < WIDTH; ++j)
        {
            tmp[i][j] = cells[i][j];
        }
    }

    for (i = 1; i < HEIGHT - 1; ++i)
    {
        for (j = 1; j < WIDTH - 1; ++j)
        {
            adjacent = cells[i - 1][j - 1] + cells[i - 1][j] + cells[i - 1][j + 1]
                        + cells[i][j - 1] + cells[i][j + 1]
                        + cells[i + 1][j - 1] + cells[i + 1][j] + cells[i + 1][j + 1];
            if (adjacent == 3)
            {
                tmp[i][j] = 1;
            }
            else if (adjacent == 2)
            {
                tmp[i][j] = cells[i][j];
            }
            else
            {
                tmp[i][j] = 0;
            }
        }
    }

    for (i = 0; i < HEIGHT; ++i)
    {
        for (j = 0; j < WIDTH; ++j)
        {
            cells[i][j] = tmp[i][j];
        }
    }

    Sleep(200);
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
