/*
 * P1605 迷宫
 * 难度：一般
 * 关键点：DFS 回溯——求的是路径条数而不是最短路，所以用 DFS 而不是 BFS
 * 核心思路：从起点 DFS，进入时标记、离开时取消，走下一步前检查是否走过，走到终点就把方案数 +1
 * 坑点：基1
 */

#include <bits/stdc++.h>
using namespace std;

int n, m, t;
int sx, sy, fx, fy;
int maze[6][6];     // 1 表示障碍，0 表示可走
bool visited[6][6]; // 当前路径是否走过
int ans = 0;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y)
{
    // 到达终点
    if (x == fx && y == fy)
    {
        ans++;
        return;
    }

    // 标记当前点已访问
    visited[x][y] = true;

    // 四个方向
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 是否合法
        if (nx < 1 || nx > n || ny < 1 || ny > m)
            continue;

        if (visited[nx][ny])
            continue;

        if (maze[nx][ny])
            continue;

        dfs(nx, ny);
    }

    // 回溯：取消标记
    visited[x][y] = false;
}

int main()
{
    cin >> n >> m >> t;
    cin >> sx >> sy >> fx >> fy;

    // 读入障碍
    for (int i = 0; i < t; i++)
    {
        int x, y;
        cin >> x >> y;
        maze[x][y] = 1;
    }

    // 起点和终点如果有障碍，直接无解（题目一般不会）
    if (maze[sx][sy] == 1 || maze[fx][fy] == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    dfs(sx, sy);

    cout << ans << endl;
    return 0;
}