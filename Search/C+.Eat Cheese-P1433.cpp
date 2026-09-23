/*
 * P2895 [USACO08FEB] Meteor Shower S
 * 难度：难！
 * 关键点：状态压缩 DP（状态穷举）
 * 核心思路：用二进制 mask 表示已吃奶酪集合
 * 坑点：n = 0 特判、浮点数精度、INF 判断
 */

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double x[15], y[15];     // 每块奶酪的坐标
double dp[1 << 15][15];  // dp数组
const double INF = 1e18; // 一个很大的数，表示“还没算出来”

// 计算第 a 块和第 b 块奶酪之间的距离
double dist(int a, int b)
{
    double dx = x[a] - x[b];
    double dy = y[a] - y[b];
    return sqrt(dx * dx + dy * dy);
}

// 计算原点到第 a 块奶酪的距离
double dist0(int a)
{
    return sqrt(x[a] * x[a] + y[a] * y[a]);
}

int main()
{
    int n;
    cin >> n;

    // 洛谷新增 Hack 数据，可能有 n = 0
    if (n == 0)
    {
        cout << "0.00" << endl;
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }

    // 初始化 dp 数组为无穷大
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            dp[mask][i] = INF;
        }
    }

    // 只吃第 i 块奶酪，从原点出发
    for (int i = 0; i < n; i++)
    {
        dp[1 << i][i] = dist0(i);
    }

    // 枚举所有“已经吃过的集合”
    for (int mask = 1; mask < (1 << n); mask++)
    {

        // 枚举最后停在哪块奶酪
        for (int i = 0; i < n; i++)
        {

            // 如果第 i 块没吃过，跳过
            if ((mask & (1 << i)) == 0)
                continue;

            // 如果这个状态还没算出来，跳过
            if (dp[mask][i] >= INF / 2)
                continue;

            // 尝试去吃下一块没吃过的奶酪 j
            for (int j = 0; j < n; j++)
            {

                // 如果第 j 块已经吃过，跳过
                if (mask & (1 << j))
                    continue;

                int newmask = mask | (1 << j);             // 新集合
                double newdist = dp[mask][i] + dist(i, j); // 新距离

                // 如果新距离更短，就更新
                if (newdist < dp[newmask][j])
                {
                    dp[newmask][j] = newdist;
                }
            }
        }
    }

    // 所有奶酪都吃过
    int full = (1 << n) - 1;

    double ans = INF;

    // 最后停在哪块都可以，取最小
    for (int i = 0; i < n; i++)
    {
        if (dp[full][i] < ans)
        {
            ans = dp[full][i];
        }
    }

    cout << fixed << setprecision(2) << ans << endl;

    return 0;
}