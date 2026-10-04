/*
 * P1162 填涂颜色
 * 难度：一般
 * 关键点：BFS/DFS 连通块、反向标记
 * 核心思路：
 *   先把所有与边界相连的 0 标记为“圈外”（outside = false），
 *   剩下的 0 就一定是被 1 包围的圈内，最后输出时改成 2。
 *   具体做法：从四条边界的每个格子出发 BFS，
 *   遇到 0 就标记为圈外，遇到 1 或已标记的格子就跳过。
 * 坑点：
 * 1. BFS 开头检查 maze[x][y] == 1 || outside[x][y] == false，避免重复入队；
 * 2. 输入的下标从 0 开始，BFS 中的边界判断用 < 0 和 >= n。
 */

#include <bits/stdc++.h>
using namespace std;

int n;
int maze[35][35];
// outside：false 表示圈外，true 表示尚未确定（最终为 true 的 0 就是圈内）
bool outside[35][35];

// 四个方向
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

void BFS(int x, int y)
{
    // 如果是 1 或已经标记过圈外，直接返回
    if (maze[x][y] == 1 || outside[x][y])
        return;

    // 队列
    queue<pair<int, int>> q;
    // 边界格子肯定是圈外
    outside[x][y] = false;
    // 起点入队
    q.push({x, y});

    while (!q.empty())
    {
        // 出队
        auto [cx, cy] = q.front();
        q.pop();

        // 四个方向
        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            // 不能越界
            if (nx < 0 || ny < 0 || nx >= n || ny >= n)
            {
                continue;
            }

            // 碰到1了或已访问
            if (maze[nx][ny] == 1 || !outside[nx][ny])
            {
                continue;
            }

            // 未访问入队
            outside[nx][ny] = false;
            q.push({nx, ny});
        }
    }
}

int main()
{
    // 录入数据
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> maze[i][j];
            outside[i][j] = true;
        }
    }

    // 从边界开始找
    for (int i = 0; i < n; i++)
    {
        // 四个边界
        BFS(0, i);
        BFS(i, 0);
        BFS(n - 1, i);
        BFS(i, n - 1);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!outside[i][j] || maze[i][j] == 1)
                cout << maze[i][j] << ' ';
            else
                cout << '2' << ' ';
        }
        cout << '\n';
    }

    return 0;
}