/*
 * P3613 【深基15.例2】寄包柜
 * 难度：一般
 * 关键点：vector + unordered_map 实现稀疏二维数组
 * 核心思路：
 *   外层用 vector，下标是寄包柜编号，O(1) 定位柜子；
 *   内层用 unordered_map，键是格子编号，值是物品编号，
 *   只存真正用过的格子，平均 O(1) 查询，空间 O(q)。
 * 坑点：
 *   1. 寄包柜编号从 1 开始，vector 要开 n+1；
 *   2. 查询时用 find 而不是 []，避免往哈希表里插入默认值 0；
 *   3. 没存过的格子输出 0。
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{

    int n, q;
    cin >> n >> q;
    // 动态数组+哈希表键值对
    vector<unordered_map<int, int>> cabinet(n + 1);

    // 一共q次
    for (int i = 0; i < q; i++)
    {
        int op;
        cin >> op;
        // 存入
        if (op == 1)
        {
            int id, grid, num;
            cin >> id >> grid >> num;
            cabinet[id][grid] = num;
        }
        // 取出
        else
        {
            int id, grid;
            cin >> id >> grid;

            auto it = cabinet[id].find(grid);
            if (it != cabinet[id].end())
                cout << it->second << '\n';
            else
                cout << 0 << '\n';
        }
    }

    return 0;
}