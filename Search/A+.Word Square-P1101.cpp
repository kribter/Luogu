/*
 * P1101 单词方阵
 * 难度：简单
 * 关键点：遍历
 * 核心思路：遍历方阵，找到所有 'y'，从每个 'y' 出发尝试 8 个方向，
 *           沿同一方向连续检查 7 个字符是否等于 "yizhong"，
 *           若匹配则把这 7 个位置在 keep 数组中标记为 true。
 * 坑点：单词之间可能交叉共用字母，所以不要直接在原数组上改，
 *       而是另开一个 keep 数组记录哪些位置属于单词，最后统一输出。
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    char g[105][105];
    bool keep[105][105] = {false};
    string target = "yizhong";
    int n;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> g[i][j];
        }
    }

    // 八个方向
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // 搜索
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (g[i][j] != 'y')
                continue;

            // 八个方向
            for (int d = 0; d < 8; d++)
            {
                // 标记是否找到
                bool ok = true;
                for (int k = 0; k < 7; k++)
                {
                    int ni = i + dx[d] * k;
                    int nj = j + dy[d] * k;
                    if (ni < 0 || ni >= n || nj < 0 || nj >= n || g[ni][nj] != target[k])
                    {
                        ok = false;
                        break;
                    }
                }

                // 找到了就更新keep
                if (ok)
                {
                    for (int k = 0; k < 7; k++)
                    {
                        int ni = i + dx[d] * k;
                        int nj = j + dy[d] * k;
                        keep[ni][nj] = true;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // 保留了吗？不然输出*
            if (keep[i][j])
                cout << g[i][j];
            else
                cout << '*';
        }
        cout << endl;
    }

    return 0;
}