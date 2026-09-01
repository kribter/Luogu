/*
 * P1228 地毯填补问题
 * 难度：难，初见没有想到怎么分解
 * 关键点：递归，分治
 * 核心思路：划分四个象限，根据已有特殊块的位置在中心放 L 型地毯
 * 坑点：可以不用数组储存的，然后是坐标系记得是左手系
 */

#include <stdio.h>
#include <string.h>

void solve(int x, int y, int a, int b, int len)
{
    if (len == 1)
        return;

    int ax = a + len / 2;
    int by = b + len / 2;
    int newlen = len / 2;
    // 左上角
    if (x < ax && y < by)
    {
        printf("%d %d %d\n", ax, by, 1);
        solve(x, y, a, b, newlen);
        solve(ax, by - 1, ax, b, newlen);
        solve(ax - 1, by, a, by, newlen);
        solve(ax, by, ax, by, newlen);
    }
    // 右上角
    else if (x < ax && y > by - 1)
    {
        printf("%d %d %d\n", ax, by - 1, 2);
        solve(ax - 1, by - 1, a, b, newlen);
        solve(ax, by - 1, ax, b, newlen);
        solve(x, y, a, by, newlen);
        solve(ax, by, ax, by, newlen);
    }
    // 左下角
    else if (x > ax - 1 && y < by)
    {
        printf("%d %d %d\n", ax - 1, by, 3);
        solve(ax - 1, by - 1, a, b, newlen);
        solve(x, y, ax, b, newlen);
        solve(ax - 1, by, a, by, newlen);
        solve(ax, by, ax, by, newlen);
    }
    // 右下角
    else
    {
        printf("%d %d %d\n", ax - 1, by - 1, 4);
        solve(ax - 1, by - 1, a, b, newlen);
        solve(ax, by - 1, ax, b, newlen);
        solve(ax - 1, by, a, by, newlen);
        solve(x, y, ax, by, newlen);
    }
}

int main()
{
    int k;
    int x, y;
    scanf("%d%d%d", &k, &x, &y);
    int len = 1;

    while (k--)
    {
        len *= 2;
    }

    solve(x, y, 1, 1, len);

    return 0;
}
