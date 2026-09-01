/*
 * P1498 南蛮图腾
 * 难度：一般
 * 关键点：递归，找到绘制起点
 * 核心思路：扶正三角形，分解子问题
 * 坑点：输出时要把三角形扶回来，记得加空格
 */

#include <stdio.h>
#include <string.h>

char map[1100][2100];

/*
/\
/__\
/\  /\
/__\/__\
/\      /\
/__\    /__\
/\  /\  /\  /\
/__\/__\/__\/__\
*/

int pow2(int n)
{
    int a = 1;
    while (n--)
    {
        a *= 2;
    }
    return a;
}

void draw(int x, int y, int n)
{
    if (n == 1)
    {
        map[x][y] = map[x + 1][y] = '/';
        map[x][y + 1] = map[x + 1][y + 3] = '\\';
        map[x + 1][y + 1] = map[x + 1][y + 2] = '_';
        return;
    }

    draw(x, y, n - 1);
    draw(x + pow2(n - 1), y, n - 1);
    draw(x + pow2(n - 1), y + pow2(n), n - 1);
}

int main()
{
    memset(map, ' ', sizeof(map));
    int n;
    scanf("%d", &n);
    draw(0, 0, n);

    int size = pow2(n);
    for (int i = 0; i < size; i++)
    {
        for (int j = 1; j < size - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < (i + 1) * 2; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}