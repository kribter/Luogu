/*
 * P1825 [USACO11OPEN] Corn Maze S
 * 难度：难
 * 关键点：BFS、传送点处理、状态设计
 * 核心思路：
 *   把每个格子看成节点，普通移动花费 1 时间，传送花费 0 时间。
 *   用 BFS 求从 '@' 到 '=' 的最短时间。
 *   踩到滑梯端点时，立刻传送到配对端点，距离只加 1（走一步踩上滑梯），
 *   传送本身不花时间。
 *
 *   关键设计：滑梯端点本身不标记为已访问，也不入队；
 *   只把配对点入队并标记距离。这样从任何路径走到滑梯端点，
 *   只要配对点还没被访问过，就能以当前距离触发传送。
 *   由于 BFS 第一次访问配对点时的距离就是最短距离，
 *   后续再踩到同一个滑梯端点也不会覆盖更优值，不会重复入队。
 *
 *   滑梯端点允许重复进入：即使它作为配对点被访问过（dist >= 0），
 *   仍然可以被再次走上去触发传送。因此跳过条件里必须排除滑梯端点。
 *
 * 坑点：
 *   1. 滑梯端点本身不要标记为已访问，否则会堵死后续可能更短的路径；
 *   2. 只标记配对点，且只检查配对点是否未访问（dist < 0）；
 *   3. 跳过条件必须允许滑梯端点重复进入：
 *      if (maze[nx][ny] == '#' || (dist[nx][ny] >= 0 && !(maze[nx][ny] >= 'A' && maze[nx][ny] <= 'Z')))
 *   4. 每个字母恰好出现两次，配对时用 v[0] 和 v[1]，别写成 v[2]；
 *   5. 起点 '@' 和终点 '=' 不是障碍，要单独处理；
 *   6. dist 初始化为 -1 表示未访问。
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    // 初始地图
    char maze[305][305];
    // 距离
    int dist[305][305];
    // 滑梯两端,最多26个
    map<char, vector<pair<int, int>>> pos;
    pair<int, int> partner[305][305];
    // 起点和终点
    pair<int, int> s;

    cin >> n >> m;

    // 初始化地图,访问记录,滑梯
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maze[i][j];
            dist[i][j] = -1;
            if (maze[i][j] >= 'A' && maze[i][j] <= 'Z')
            {
                pos[maze[i][j]].push_back({i, j});
            }
            else if (maze[i][j] == '@')
                s = {i, j};
        }
    }

    // 滑梯配对
    for (auto &[ch, v] : pos)
    {
        int x1 = v[0].first, x2 = v[1].first;
        int y1 = v[0].second, y2 = v[1].second;
        partner[x1][y1] = {x2, y2};
        partner[x2][y2] = {x1, y1};
    }

    // BFS队列
    queue<pair<int, int>> q;

    // 四个方向
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    // 起点入队并标记
    q.push(s);
    dist[s.first][s.second] = 0;

    // BFS
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
            if (nx < 0 || ny < 0 || nx >= n || ny >= m)
            {
                continue;
            }

            // 不能通行/走过了(且非滑梯端口)
            if (maze[nx][ny] == '#' || (dist[nx][ny] >= 0 && !(maze[nx][ny] >= 'A' && maze[nx][ny] <= 'Z')))
            {
                continue;
            }

            // 到终点了
            if (maze[nx][ny] == '=')
            {
                // 更新距离并结束
                dist[nx][ny] = dist[cx][cy] + 1;
                cout << dist[nx][ny] << endl;
                return 0;
            }

            // 正常格子
            if (maze[nx][ny] == '.')
            {
                // 入队并更新距离
                q.push({nx, ny});
                dist[nx][ny] = dist[cx][cy] + 1;
            }

            // 滑梯端点
            if (maze[nx][ny] >= 'A' && maze[nx][ny] <= 'Z')
            {
                // 获取配对点
                auto [px, py] = partner[nx][ny];

                // 如果配对点未访问，才入队
                if (dist[px][py] < 0)
                {
                    q.push({px, py});
                    dist[px][py] = dist[cx][cy] + 1;
                }
            }
        }
    }

    return 0;
}