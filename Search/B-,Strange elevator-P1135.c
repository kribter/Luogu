/*
 * P1135 奇怪的电梯
 * 难度：一般
 * 关键点：队列
 * 核心思路：一条马的翻版，把移动方向变成上下楼
 * 坑点：无
 */

#include <stdio.h>

int line[205]; // 每层楼信息
int ans[205];  // 到达信息
int q[205];    // 队列
int start = 0, end = 0;

void BFS(int n, int a, int b)
{
    // 初始化
    for (int i = 1; i <= n; i++)
        ans[i] = -1;
    ans[a] = 0;

    // 入队
    q[end] = a;
    end++;

    // BFS
    while (start < end)
    {
        int down = q[start] - line[q[start]];
        int up = q[start] + line[q[start]];
        if (down > 0 && down <= n && ans[down] == -1)
        {
            ans[down] = ans[q[start]] + 1;
            // 入队
            q[end] = down;
            end++;
        }
        if (up > 0 && up <= n && ans[up] == -1)
        {
            ans[up] = ans[q[start]] + 1;
            // 入队
            q[end] = up;
            end++;
        }
        if (up == b || down == b)
        {
            return;
        }

        start++;
    }
}

int main()
{
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &line[i]);
    }

    BFS(n, a, b);

    printf("%d", ans[b]);

    return 0;
}
