/*
 * P2895 [USACO08FEB] Meteor Shower S
 * 难度：难，要抽象出来
 * 关键点：BFS，抽象
 * 核心思路：创建一个destroy数组，作为每次BFS的约束，不要模拟而是把整个东西抽象出来。
 * 坑点：BFS，边界判断，位置判断，出队入队
 */

#define INF 0x3f3f3f3f

#include <stdio.h>
#include <string.h>

// 摧毁的
int destroy[305][305];
// 地图
int dist[305][305];
int n;
// 队列
int qx[90000], qy[90000];
//  四个方向+原地
int move[5][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0}};

void BFS()
{
    int head = 0, rear = 0;

    // 出生点被摧毁了
    if (destroy[0][0] == 0)
    {
        printf("-1");
        return;
    }

    // 初始化
    dist[0][0] = 0;
    qx[rear] = 0;
    qy[rear] = 0;
    rear++;

    while (head < rear)
    {
        int x = qx[head], y = qy[head];
        head++;

        // 出队时判断当前格子是否安全
        if (destroy[x][y] == INF)
        {
            printf("%d\n", dist[x][y]);
            return;
        }

        for (int j = 0; j < 4; j++)
        {
            int nx = x + move[j][0];
            int ny = y + move[j][1];

            if (nx < 0 || nx >= 305 || ny < 0 || ny >= 305)
                continue;
            if (dist[nx][ny] != -1)
                continue; // 已访问
            int nt = dist[x][y] + 1;
            if (nt >= destroy[nx][ny])
                continue; // 到达时已被摧毁

            dist[nx][ny] = nt;
            qx[rear] = nx;
            qy[rear] = ny;
            rear++;
        }
    }

    // 找完都没有
    printf("-1");
    return;
}

int main()
{
    scanf("%d", &n);

    // 初始化陨石会落下的地方
    memset(destroy, 0x3f, sizeof(destroy)); // 全部变成 0x3f3f3f3f
    memset(dist, -1, sizeof(dist));         // 全部变成 -1
    for (int i = 0; i < n; i++)
    {
        int x, y, t;
        scanf("%d%d%d", &x, &y, &t);
        for (int j = 0; j < 5; j++)
        {
            int nx = x + move[j][0];
            int ny = y + move[j][1];
            if (nx < 0 || nx >= 305 || ny < 0 || ny >= 305)
                continue;
            if (destroy[nx][ny] > t)
                destroy[nx][ny] = t;
        }
    }

    // BFS
    BFS();

    return 0;
}
