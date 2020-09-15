#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 50
#define TARGET 5

void init();
void show();
void updateWithInput();
void updateWithoutInput();
void gotoxy(int x, int y);
void hide();

int canvas[HEIGHT][WIDTH] = {0}; //0:space; 1:plane; 2:bullet; 3:target;
int plane_x, plane_y;
int target_x[TARGET], target_y[TARGET];
int score;
int weapon;

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
    plane_x = WIDTH / 2;
    plane_y = HEIGHT / 2;
    canvas[plane_y][plane_x] = 1;
    for (int i = 0; i < TARGET; ++i)
    {
        target_x[i] = rand() % WIDTH;
        target_y[i] = 0;
        canvas[target_y[i]][target_x[i]] = 3;
    }
    score = 0;
    weapon = 0;
    hide();
    for (int i = 0; i <= HEIGHT; ++i)
    {
        for (int j = 0; j <= WIDTH; ++j)
        {
            if ((i == HEIGHT) || (j == WIDTH))
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
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (canvas[i][j] == 1)
            {
                printf("*");
            }
            else if (canvas[i][j] == 2)
            {
                printf("|");
            }
            else if (canvas[i][j] == 3)
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
    printf("\n\nScore: %d ", score);
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
                canvas[plane_y][plane_x] = 0;
                plane_y--;
                canvas[plane_y][plane_x] = 1;
            }
        }
        if (plane_y != HEIGHT - 1)
        {
            if (input == 's' || input == 'S')
            {
                canvas[plane_y][plane_x] = 0;
                plane_y++;
                canvas[plane_y][plane_x] = 1;
            }
        }
        if (plane_x != 0)
        {
            if (input == 'a' || input == 'A')
            {
                canvas[plane_y][plane_x] = 0;
                plane_x--;
                canvas[plane_y][plane_x] = 1;
            }
        }
        if (plane_x != WIDTH - 1)
        {
            if (input == 'd' || input == 'D')
            {
                canvas[plane_y][plane_x] = 0;
                plane_x++;
                canvas[plane_y][plane_x] = 1;
            }
        }
        if (input == ' ')
        {
            int left = plane_x - weapon, right = plane_x + weapon;
            if (left < 0)
            {
                left = 0;
            }
            if (right > WIDTH - 1)
            {
                right = WIDTH - 1;
            }
            for (int i = left; i <= right; ++i)
            {
                canvas[plane_y - 1][i] = 2;
            }
        }
    }
}

void updateWithoutInput()
{
    int i, j, k;
    for (i = 0; i < HEIGHT; ++i)
    {
        for (j = 0; j < WIDTH; ++j)
        {
            if (canvas[i][j] == 2)
            {
                for (k = 0; k < TARGET; ++k)
                {
                    if (i == target_y[k] && j == target_x[k])
                    {
                        canvas[target_y[k]][target_x[k]] = 0;
                        target_y[k] = 0;
                        target_x[k] = rand() % WIDTH;
                        canvas[target_y[k]][target_x[k]] = 3;
                        score++;
                        if (score % 3 == 0)
                        {
                            weapon++;
                        }
                    }
                }
                canvas[i][j] = 0;
                if (i > 0)
                {
                    canvas[i - 1][j] = 2;
                }
            }
        }
    }

    for (k = 0; k < TARGET; ++k)
    {
        if (target_y[k] > HEIGHT)
        {
            canvas[target_y[k]][target_x[k]] = 0;
            target_y[k] = 0;
            target_x[k] = rand() % WIDTH;
            canvas[target_y[k]][target_x[k]] = 3;
            score--;
        }
    }

    static int speed = 0;
    if (speed < 20 - score / 2)
    {
        speed++;
    }
    if (speed >= 20 - score / 2)
    {
        for (k = 0; k < TARGET; ++k)
        {
            canvas[target_y[k]][target_x[k]] = 0;
            target_y[k]++;
            canvas[target_y[k]][target_x[k]] = 3;
            speed = 0;
        }
    }

    for (i = 0; i < TARGET; ++i)
    {
        if ((plane_x == target_x[i]) && (plane_y == target_y[i]))
        {
            printf("\n>_<\npress ENTER to exit...");
            getchar();
            exit(0);
        }
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
