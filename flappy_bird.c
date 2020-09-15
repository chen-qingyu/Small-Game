#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void init();
void show();
void updateWithInput();
void updateWithoutInput();
void gotoxy(int x, int y);
void hide();

int height, width;
int bird_x, bird_y;
int bar_x, bar_y1, bar_y2;
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
    width = 20;
    height = 20;
    bird_x = width / 4;
    bird_y = 0;
    bar_x = width;
    bar_y1 = height / 4;
    bar_y2 = height / 2;
    score = 0;
    hide();
}

void show()
{
    gotoxy(0, 0);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if ((i == bird_y) && (j == bird_x))
            {
                printf("@");
            }
            else if ((j == bar_x) && ((i <= bar_y1) || (i >= bar_y2)))
            {
                printf("|");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Fly: SPACE\n");
    printf("Score: %d", score);
}

void updateWithInput()
{
    char input;

    if (kbhit())
    {
        input = getch();

        if (input == ' ')
        {
            bird_y -= 2;
        }
    }
}

void updateWithoutInput()
{
    bird_y++;

    if ((bird_y < 0) || (bird_y > height))
    {
        printf("\n>_<\npress ENTER to exit...");
        getchar();
        exit(0);
    }

    if (bar_x > 0)
    {
        bar_x--;
    }
    else
    {
        bar_x = width;
        bar_y1 = rand() % (height * 3 / 4);
        bar_y2 = bar_y1 + height / 4;
    }

    if (bird_x == bar_x)
    {
        if ((bird_y > bar_y1) && (bird_y < bar_y2))
        {
            score++;
            printf("\a");
        }
        else
        {
            printf("\n>_<\npress ENTER to exit...");
            getchar();
            exit(0);
        }
    }

    Sleep(150);
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
