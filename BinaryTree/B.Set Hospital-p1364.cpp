/*
 * P1364 医院设置
 * 难度：难
 * 关键点：树的遍历（DFS）、暴力枚举
 * 核心思路：
 *   因为 n <= 100，可以暴力枚举医院建在哪个节点。
 *   对于每个枚举的节点，通过 DFS 遍历整棵树，计算所有人到该节点的距离和。
 *   DFS 利用 father, left, right 三个指针走遍全树，vis 数组防止走回头路。
 *   对于每个节点，贡献的距离为：当前节点人数 * 当前距离 d。
 *   取所有节点作为医院时的最小距离和即为答案。
 * 坑点：
 *   1. 树是无向的，遍历时既要去左右子树，也要去父节点，必须用 vis 防重；
 *   2. 节点编号为 0 表示空，赋值 father 时要特判一下，避免误改 t[0]；
 *   3. ans 初始值要设得足够大。
 */

#include <bits/stdc++.h>
using namespace std;

struct node
{
    // 左右子树及父节点
    int father, left, right;
    // 人数
    int value;
} t[105];

// 标记节点是否访问过
int vis[105];

// 求在当前节点建医院的距离和
int cal(int x, int d)
{
    // 已经访问过了/超出范围了==》DFS不走回头路
    if (vis[x] || !x)
        return 0;

    vis[x] = 1;

    // DFS
    return cal(t[x].father, d + 1) + cal(t[x].left, d + 1) + cal(t[x].right, d + 1) + t[x].value * d;
}

int main()
{
    int n;
    cin >> n;

    // 处理输入
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i].value >> t[i].left >> t[i].right;
    }

    // 父节点
    for (int i = 1; i <= n; i++)
    {
        t[t[i].left].father = i;
        t[t[i].right].father = i;
    }

    int ans = 10e7;

    for (int i = 1; i <= n; i++)
    {
        // 置0
        memset(vis, 0, sizeof(vis));

        ans = min(ans, cal(i, 0));
    }

    cout << ans;

    return 0;
}

/*
 * P1364 医院设置
 * 关键点：树的遍历（BFS）、暴力枚举
 * 核心思路：
 *   因为 n <= 100，可以暴力枚举医院建在哪个节点。
 *   对于每个枚举的节点，通过 BFS 遍历整棵树，计算所有人到该节点的距离和。
 *   树的边是无向的，每个节点最多连着 3 个点（左孩子、右孩子、父节点）。
 *   BFS 队列里存 {节点编号, 距离}，vis 数组防止走回头路。
 *   取所有节点作为医院时的最小距离和即为答案。
 * 坑点：
 *   1. 树是无向的，BFS 遍历时既要去左右子树，也要去父节点，必须用 vis 防重；
 *   2. 节点编号为 0 表示空，入队时要特判非 0；
 *   3. ans 初始值要设得足够大。

#include <bits/stdc++.h>
using namespace std;

struct node
{
    int father, left, right;
    int value;
} t[105];

int vis[105];

// 以 start 为医院，BFS 计算总距离
int bfs(int start)
{
    memset(vis, 0, sizeof(vis));

    queue<pair<int, int>> q; // {节点编号, 距离}
    q.push({start, 0});
    vis[start] = 1;

    int total_dist = 0;

    while (!q.empty())
    {
        auto [u, d] = q.front();
        q.pop();

        // 累加该节点所有人的距离贡献
        total_dist += t[u].value * d;

        // 尝试走向三个邻居：父节点、左孩子、右孩子
        int neighbors[3] = {t[u].father, t[u].left, t[u].right};

        for (int i = 0; i < 3; i++)
        {
            int v = neighbors[i];
            // 如果邻居存在，且没被访问过
            if (v != 0 && !vis[v])
            {
                vis[v] = 1;
                q.push({v, d + 1});
            }
        }
    }

    return total_dist;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> t[i].value >> t[i].left >> t[i].right;
    }

    // 建立父节点指针
    for (int i = 1; i <= n; i++)
    {
        if (t[i].left)
            t[t[i].left].father = i;
        if (t[i].right)
            t[t[i].right].father = i;
    }

    int ans = 1e9; // 初始化为一个很大的数

    // 枚举每一个节点作为医院
    for (int i = 1; i <= n; i++)
    {
        ans = min(ans, bfs(i));
    }

    cout << ans << '\n';

    return 0;
}
*/