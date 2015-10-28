#include <stdio.h>


int matrix_route[5][5] = {
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0},
    {0, 0/*1:failure case*/, 0, 0, 0}};

int can_go_left(int x, int y)
{
    if (y - 1 >= 0)
        return (matrix_route[x][y - 1] == 0);
    else
        return 0;
}

int can_go_below(int x, int y)
{
    if (x + 1 < 5)
        return (matrix_route[x + 1][y] == 0);
    else
        return 0;
}

void advance_route(int x, int y)
{
    int ret;
    printf("cur=%d %d %d\n", x, y, matrix_route[x][y]);

    if (x == 4 && y == 0) {
        printf("found!\n");
        return;
    }

    if (can_go_left(x, y))
        advance_route(x, y - 1);

    if (can_go_below(x, y))
        advance_route(x + 1, y);

}

int main(void)
{
    advance_route(0, 4);

    return 0;
}
