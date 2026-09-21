/*
 * P1443 马的遍历
 * 难度：初见难，特别是数据结构的构建
 * 关键点：BFS,数据结构
 * 核心思路：先走完这一层再往下走
 * 坑点：基0/1，数据结构的选择
 * 杂谈：BFS起点。
 */

#include <stdio.h>

int map[405][405];            // 地图
int q_x[160000], q_y[160000]; // 队列
int start = 0, end = 0;       // 队列头和末
// 马的一次移动坐标偏移量
int move[8][2] = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

void BFS(int n, int m, int x, int y)
{
    // 初始化地图
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            map[i][j] = -1;
    map[x][y] = 0;

    // 入队
    q_x[end] = x, q_y[end] = y;
    end++; // 下一个空位

    // BFS
    while (start < end)
    {
        int nx, ny;
        // 枚举8个方向
        for (int i = 0; i < 8; i++)
        {
            nx = q_x[start] + move[i][0];
            ny = q_y[start] + move[i][1];

            // 超出地图
            if (nx < 1 || ny < 1 || nx > n || ny > m)
                continue;
            // 已经走过了
            if (map[nx][ny] != -1)
                continue;

            // 更新
            map[nx][ny] = map[q_x[start]][q_y[start]] + 1;
            q_x[end] = nx;
            q_y[end] = ny;
            end++;
        }
        // 移到下一个
        start++;
    }
}

int main()
{
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    BFS(n, m, x, y);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}
