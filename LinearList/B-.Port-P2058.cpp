/*
 * P2058 [NOIP 2016 普及组] 海港
 * 难度：一般
 * 关键点：队列、滑动窗口、哈希表
 * 核心思路：
 *   队列存每艘船（到达时间 + 国籍列表），维护 24 小时滑动窗口。
 *   用 unordered_map 统计窗口内每个国籍的人数。
 *   新船入队时更新计数和 sum，队头超时则出队并更新计数和 sum。
 * 坑点：
 *   1. 时间差正好等于 86400 的船要弹出，用 >= 不是 >；
 *   2. 国籍编号可能很大，用 unordered_map 不用固定数组；
 *   3. sum 只在国籍人数 0→1 时 +1，1→0 时 -1。
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{

    // 队列+键值对（时间+可变数组）
    queue<pair<int, vector<int>>> arrive;

    // 国家标记，初始置0
    unordered_map<int, int> country;

    // 现有国籍数量
    int sum = 0;

    int n, k, t;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        pair<int, vector<int>> ship;
        cin >> t >> k;

        // 到达时间
        ship.first = t;

        // 登记船上国籍
        for (int j = 0; j < k; j++)
        {
            int x;
            cin >> x;
            ship.second.push_back(x);

            // 新增国籍
            if (country[x] == 0)
                sum++;

            country[x]++;
        }

        // 新船入队
        arrive.push(ship);

        // 如果不为空且前面的超时了
        while (!arrive.empty() && ship.first - arrive.front().first >= 86400)
        {
            // 弹出并记录
            auto outship = arrive.front();
            arrive.pop();

            // 对应国籍人数减少
            for (int x : outship.second)
            {
                country[x]--;
                // 如果该国籍人数变成0，则总国籍数量变少
                if (country[x] == 0)
                    sum--;
            }
        }

        cout << sum << endl;
    }

    return 0;
}