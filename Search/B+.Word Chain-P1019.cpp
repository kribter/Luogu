/*
 * P1019 [NOIP 2000 提高组] 单词接龙（疑似错题）
 * 难度：一般
 * 关键点：数据结构，DFS
 * 核心思路：先预处理出单词两两之间的最短重叠长度，存成关系表，
 *           然后从以给定字母开头的单词出发 DFS，每次查表尝试接龙，
 *           更新最大长度，回溯时恢复单词使用次数。
 * 坑点：
 *   1. 重叠部分要取最短，不是最长（这样龙才最长）；
 *   2. 每个单词最多用两次，要用 used[] 计数；
 *   3. 不能存在包含关系，枚举重叠长度时最大只能到 min(l1, l2) - 1；
 *   4. 开头字母可能对应多个单词，每个都要作为起点试一遍；
 *   5. 字符串操作用 string 的 substr，注意 substr(0, k) 是取前 k 个字符。
 */

#include <bits/stdc++.h>
using namespace std;

// 单词组
string word[25];
// 使用次数
int used[25] = {0};
// 长度
int len[25];

// 目前最长
int maxlen = 0;

// 单词关系，dist[i][j]表示i的末尾和j的开始有多少重复
int dist[25][25];

// BFS
void BFS(int id, int n, int nowLen)
{
    // BFS
    for (int i = 0; i < n; i++)
    {
        // 有后续的
        if (dist[id][i] > 0 && used[i] < 2)
        {
            // 更新数据
            nowLen += (len[i] - dist[id][i]);
            used[i]++;
            BFS(i, n, nowLen);

            // 回溯
            nowLen -= (len[i] - dist[id][i]);
            used[i]--;
        }
    }

    if (maxlen < nowLen)
        maxlen = nowLen;
    return;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> word[i];
        len[i] = word[i].length();
    }
    char start;
    cin >> start;

    // 建立单词关系
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int l1 = len[i];
            int l2 = len[j];

            // 最大枚举长度
            int maxtest = min(l1, l2) - 1;
            dist[i][j] = 0; // 默认不能接
            for (int k = 1; k <= maxtest; k++)
            {
                if (word[i].substr(l1 - k) == word[j].substr(0, k))
                {
                    // 因为要重叠尽量短
                    dist[i][j] = k;
                    break;
                }
            }
        }
    }

    // 找start word
    for (int i = 0; i < n; i++)
    {
        if (word[i][0] == start)
        {
            used[i]++;
            BFS(i, n, len[i]);
            used[i]--;
        }
    }

    cout << maxlen << endl;

    return 0;
}