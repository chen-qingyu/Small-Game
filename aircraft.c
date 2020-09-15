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
int plane_x, plane_y;
int bullet_x, bullet_y;
int target_x, target_y;
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
    width = 40;
    height = 20;
    plane_x = width / 2;
    plane_y = height / 2;
    bullet_x = plane_x;
    bullet_y = -1;
    target_x = width / 2;
    target_y = 0;
    score = 0;
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
    printf("Move: W S A D; Fire: SPACE\n");
}

void show()
{
    gotoxy(0, 0);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if ((i == plane_y) && (j == plane_x))
            {
                printf("*");
            }
            else if ((i == bullet_y) && (j == bullet_x))
            {
                printf("|");
            }
            else if ((i == target_y) && (j == target_x))
            {
                printf("@");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n\nScore: %d", score);
}

void updateWithInput()
{
    char input;

    if (kbhit())
    {
        input = getch();

        if (plane_y != 0)
        {
            if (input == 'w' || input == 'W')
            {
                plane_y--;
            }
        }
        if (plane_y != height - 1)
        {
            if (input == 's' || input == 'S')
            {
                plane_y++;
            }
        }
        if (plane_x != 0)
        {
            if (input == 'a' || input == 'A')
            {
                plane_x--;
            }
        }
        if (plane_x != width - 1)
        {
            if (input == 'd' || input == 'D')
            {
                plane_x++;
            }
        }
        if (input == ' ')
        {
            bullet_y = plane_y;
            bullet_x = plane_x;
        }
    }
}

void updateWithoutInput()
{
    if ((bullet_x == target_x) && (bullet_y == target_y))
    {
        printf("\a");
        score++;
        target_y = 0;
        target_x = rand() % width;
        bullet_y = -1;
    }

    if ((plane_x == target_x) && (plane_y == target_y))
    {
        printf("\n>_<\npress ENTER to exit...");
        getchar();
        exit(0);
    }

    static int speed = 0;
    if (speed < 20 - score)
    {
        speed++;
    }

    if (target_y > height)
    {
        target_y = 0;
        target_x = rand() % width;
    }
    else
    {
        if (speed >= 20 - score)
        {
            target_y++;
            speed = 0;
        }
    }
    if (bullet_y > -1)
    {
        bullet_y--;
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
