/*
 * P4913 【深基16.例3】二叉树深度
 * 难度：一般
 * 关键点：二叉树，BFS/DFS，深度
 * 核心思路：用数组模拟二叉树，用DFS/BFS
 * 坑点：基1
 */

#include <bits/stdc++.h>
using namespace std;

// 左右子树
int lc[1000005], rc[1000005];

int getDep(int id)
{
    if (id == 0)
        return 0;
    return 1 + max(getDep(lc[id]), getDep(rc[id]));
}

int main()
{

    // 总节点数量
    int n;
    cin >> n;

    // 读入信息,注意是基1的
    for (int i = 1; i <= n; i++)
        cin >> lc[i] >> rc[i];

    // 开始统计

    // DFS，可能会爆栈
    //  cout << getDep(1);

    // BFS，不会爆栈
    queue<pair<int, int>> q; // 节点编号, 深度
    q.push({1, 1});
    int ans = 0;

    while (!q.empty())
    {
        auto [id, dep] = q.front();
        q.pop();
        ans = max(ans, dep);

        if (lc[id])
            q.push({lc[id], dep + 1});
        if (rc[id])
            q.push({rc[id], dep + 1});
    }

    cout << ans << '\n';

    return 0;
}