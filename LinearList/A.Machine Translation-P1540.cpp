/*
 * P1540 [NOIP 2010 提高组] 机器翻译
 * 难度：
 * 关键点：队列、标记数组
 * 核心思路：
 *   队列模拟内存，bool 数组标记单词是否在内存中。
 *   遇到单词先查标记：
 *     不在 → 查词典次数 +1，入队并标记；
 *            若队列超过 m，弹出队头并取消标记。
 *     在   → 跳过。
 * 坑点：
 *   1. 单词编号 ≤ 1000，标记数组要开 1005，不是 n；
 *   2. 判断队列是否满，用 q.size() > m 或累计入队次数；
 *   3. 弹出队头时别忘了取消标记。
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    // 标记是否存在
    bool sign[1005] = {};

    // 队列（内存）
    queue<int> q;

    int ans = 0;
    // 翻译
    for (int i = 0; i < n; i++)
    {
        int word;
        cin >> word;

        // 如果没有
        if (!sign[word])
        {
            ans++;
            q.push(word);
            sign[word] = true;
            // 如果超了
            if ((int)q.size() > m)
            {
                int head = q.front();
                q.pop();
                sign[head] = false;
            }
        }
    }

    cout << ans;

    return 0;
}