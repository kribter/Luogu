/*
 * P1596 [USACO10OCT] Lake Counting S
 * 难度：简单
 * 关键点：BFS/DFS 求连通块
 * 核心思路：遍历网格，遇到未访问的 'W' 就启动一次 BFS，
 *           把与它相连的所有 'W' 标记为已访问，池塘数 +1。
 * 坑点：
 *   1. 边界判断用 < 0 和 >= n / >= m，不是 <= 0；
 *   2. 只有未访问且是 'W' 的格子才入队，入队时立刻标记 visited；
 *   3. 用 STL queue 时，push 用 q.push({x, y})，取队头后记得 q.pop()；
 *   4. 数组下标从 0 开始，输入也要从 0 开始读；
 *   5. pair 里第一个是行，第二个是列，别写反。
 */

#include <bits/stdc++.h>
using namespace std;

// 地理信息
int n, m;
char grids[105][105];
// 八个方向
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 访问记录
int visited[105][105] = {0};

// 池塘数量
int ans = 0;

// BFS
void BFS(int x, int y)
{
    // C++自己带的队列数据结构
    queue<pair<int, int>> q;

    // 起点入队
    q.push({x, y});
    visited[x][y] = 1;

    while (!q.empty())
    {
        // 出队
        auto [cx, cy] = q.front();
        q.pop();

        // 八个方向
        for (int i = 0; i < 8; i++)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            // 边界
            if (nx < 0 || ny < 0 || nx >= n || ny >= m)
            {
                continue;
            }

            // 未访问+水
            if (visited[nx][ny] == 0 && grids[nx][ny] == 'W')
            {
                visited[nx][ny] = 1;
                // 入队
                q.push({nx, ny});
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grids[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // 如果找到新水格
            if (!visited[i][j] && grids[i][j] == 'W')
            {
                BFS(i, j);
                ans++;
            }
        }
    }

    cout << ans;

    return 0;
}