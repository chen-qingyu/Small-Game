#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

// 地图元素
#define WALL 1
#define ROAD 0
#define START 2
#define END 3

// 方向
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// 最大记录步骤
#define MAX_STEP (1024 * 2)

// 最大地图尺寸
#define MAX_SIZE 1024

// 地图
int map[MAX_SIZE][MAX_SIZE];

// 步骤
int step_arr[MAX_STEP] = {0};

// 重来标记
int reset_flag = 0;

/* Function prototypes for functions */
void menu(void);
void init_map(void);
void create_map(int x, int y);
int get_key();
void draw_point(int x, int y);
void game();
void print_step();

/* Function prototypes for helper functions */
static void move_cursor(int x, int y);
static void hide_cursor();

// 迷宫的高度，必须为奇数
int height = 25;
// 迷宫的宽度，必须为奇数
int width = 25;

int main()
{
    do
    {
        menu();
        init_map();
        game();
    } while (reset_flag);
    print_step();

    return 0;
}

void menu(void)
{
    system("cls");

    printf("Welcome to the maze game!\n");
    printf("\n");
    printf(" - 1. Start game with default size 25 x 25.\n");
    printf(" - 2. Set size.\n");
    printf(" - 0. Exit.\n");
    printf("Your choice: ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1)
    {
        height = 25;
        width = 25;
    }

    if (choice == 2)
    {
        printf("Please input the size of map.\n");
        printf("Size must be odd, space separation.\n");
        printf("height width = ");
        scanf("%d %d", &height, &width);
        int is_too_big = (height >= MAX_SIZE) || (width >= MAX_SIZE);
        int is_too_small = (height <= 1) || (width <= 1);
        int is_even = (height % 2 == 0) || (width % 2 == 0);
        while (is_too_big || is_too_small || is_even)
        {
            if (is_too_big)
            {
                printf("Size must < %d.\n", MAX_SIZE);
            }
            if (is_too_small)
            {
                printf("Size must > 1.\n");
            }
            if (is_even)
            {
                printf("Size must be odd.\n");
            }
            printf("Please input again.\n");
            printf("height width = ");
            scanf("%d %d", &height, &width);
            is_too_big = (height >= MAX_SIZE) || (width >= MAX_SIZE);
            is_too_small = (height <= 1) || (width <= 1);
            is_even = (height % 2 == 0) || (width % 2 == 0);
        }
    }

    if (choice == 0)
    {
        exit(0);
    }

    system("cls");
}

void init_map(void)
{
    // 标题
    system("title Maze Game");
    // 初始化随机种子
    srand(time(NULL));
    // 隐藏光标
    hide_cursor();

    for (int i = 0; i < MAX_STEP; i++)
    {
        step_arr[i] = 0;
    }

    reset_flag = 0;

    // 初始化迷宫
    for (int i = 0; i <= height + 1; i++)
    {
        for (int j = 0; j <= width + 1; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                map[i][j] = ROAD;
            }
            else
            {
                map[i][j] = WALL;
            }
        }
    }

    // 从随机一个点开始生成迷宫，该点行列都为偶数
    create_map(2 * (rand() % (height / 2) + 1), 2 * (rand() % (width / 2) + 1));

    // 边界处理
    for (int i = 0; i <= height + 1; i++)
    {
        map[i][0] = WALL;
        map[i][width + 1] = WALL;
    }
    for (int j = 0; j <= width + 1; j++)
    {
        map[0][j] = WALL;
        map[height + 1][j] = WALL;
    }

    // 给定入口
    map[2][1] = START;
    // 给定出口
    map[height - 1][width] = END;

    // 画出迷宫
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            draw_point(i, j);
        }
    }

    move_cursor(2 * width + 2, 0);
    printf("Press E to end game.");
    move_cursor(2 * width + 2, 2);
    printf("Press R to restart game.");
    move_cursor(2 * width + 2, 4);
    printf("Press Q to quit game.");
}

// 递归生成具有唯一通路的迷宫
void create_map(int x, int y)
{
    // 四个方向
    int c[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

    // 将方向打乱
    for (int i = 0; i < 4; i++)
    {
        int j = rand() % 4;
        int t = c[i][0];
        c[i][0] = c[j][0];
        c[j][0] = t;
        t = c[i][1];
        c[i][1] = c[j][1];
        c[j][1] = t;
    }

    map[x][y] = ROAD;

    // 递归
    for (int i = 0; i < 4; i++)
    {
        if (map[x + 2 * c[i][0]][y + 2 * c[i][1]] == WALL)
        {
            map[x + c[i][0]][y + c[i][1]] = ROAD;
            create_map(x + 2 * c[i][0], y + 2 * c[i][1]);
        }
    }
}

// 接收按键
int get_key()
{
    char c;
    while (c = getch())
    {
        if (c == 'R' || c == 'r' ||
            c == 'Q' || c == 'q' ||
            c == 'E' || c == 'e')
        {
            return c;
        }
        if (c == -32)
        {
            switch (c = getch())
            {
                case 72:
                    return LEFT;
                    break;
                case 80:
                    return RIGHT;
                    break;
                case 75:
                    return UP;
                    break;
                case 77:
                    return DOWN;
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

// 画迷宫中的一点
void draw_point(int x, int y)
{
    move_cursor(2 * y - 2, x - 1);
    switch (map[x][y])
    {
        // 画入口
        case START:
            printf(">");
            break;
        // 画出口
        case END:
            printf(">");
            break;
        // 画墙
        case WALL:
            printf("#");
            break;
        // 画路
        case ROAD:
            printf(" ");
            break;
        default:
            break;
    }
}

void game()
{
    int x = 2, y = 1; // 玩家当前位置，刚开始在入口处
    int c;            // 接收按键
    int step = 0;
    step_arr[step] = x;
    step_arr[step + 1] = y;
    step += 2;
    while (1)
    {
        move_cursor(2 * y - 2, x - 1);
        printf("@"); // 画出玩家当前位置

        if (map[x][y] == END) // 判断是否到达出口
        {
            move_cursor(0, height);
            printf("Great!~\n");
            break;
        }

        c = get_key();
        if (c == 'E' || c == 'e')
        {
            move_cursor(0, height);
            printf("End game.\n");
            break;
        }
        if (c == 'R' || c == 'r')
        {
            reset_flag = 1;
            break;
        }
        if (c == 'Q' || c == 'q')
        {
            printf("Boodbye.\n");
            exit(0);
        }
        switch (c)
        {
            case LEFT:
                if (map[x - 1][y] != WALL)
                {
                    draw_point(x, y);
                    x--;
                    step_arr[step] = x;
                    step_arr[step + 1] = y;
                    step += 2;
                }
                break;
            case RIGHT:
                if (map[x + 1][y] != WALL)
                {
                    draw_point(x, y);
                    x++;
                    step_arr[step] = x;
                    step_arr[step + 1] = y;
                    step += 2;
                }
                break;
            case UP:
                if (map[x][y - 1] != WALL)
                {
                    draw_point(x, y);
                    y--;
                    step_arr[step] = x;
                    step_arr[step + 1] = y;
                    step += 2;
                }
                break;
            case DOWN:
                if (map[x][y + 1] != WALL)
                {
                    draw_point(x, y);
                    y++;
                    step_arr[step] = x;
                    step_arr[step + 1] = y;
                    step += 2;
                }
                break;
            default:
                break;
        }
    }
}

void print_step()
{
    move_cursor(0, height + 2);
    printf("step: (x, y)\n");
    for (int i = 0; step_arr[i] != 0 && step_arr[i + 1] != 0; i += 2)
    {
        printf("%4d: (%d, %d)\n", (i / 2) + 1, step_arr[i + 1] - 1, step_arr[i] - 1);
    }
    getch();
}

/* Helper Functions */

// 移动光标
static void move_cursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 隐藏光标
static void hide_cursor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = 0; //赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut, &cci);
}
