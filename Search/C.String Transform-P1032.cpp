/*
 * P1032 [NOIP 2002 提高组] 字串变换（疑似错题）
 * 难度：难
 * 关键点：BFS、字符串替换、去重
 * 核心思路：
 *   把每个字符串看成一个状态，每次变换看成一步。
 *   用 BFS 按步数一层层扩展，第一次遇到 B 时的步数就是最少步数。
 *   每次变换对每条规则，找到所有匹配位置，分别生成新字符串入队。
 *   用 unordered_set 记录出现过的字符串，防止重复搜索。(我的天哪哈希表大人)
 * 坑点：
 *   1. 输入规则数量不确定，用 while (cin >> a >> b) 读到 EOF；
 *   2. 一次变换只替换一个位置，同一子串出现多次要分别生成；
 *   3. 必须去重，否则队列爆炸；
 *   4. 步数超过 10 不再扩展；
 *   5. 起点等于终点时输出 0；
 *   6. find 返回 size_t，比较用 string::npos。
 */

#include <bits/stdc++.h>
using namespace std;

// C++动态数组
vector<pair<string, string>> rules;
// C++哈希表,O(1)级查询速度
unordered_set<string> visited;

// 获得替换后
vector<string> getNext(string s, string from, string to)
{
    // 所有替换结果
    vector<string> res;

    // 找from直到找不到
    size_t pos = s.find(from, 0);
    while (pos != string::npos)
    {
        // 拼接出新的字符串
        string next = s.substr(0, pos) + to + s.substr(pos + from.length());

        // 加入res
        res.push_back(next);

        // 更新pos
        pos = s.find(from, pos + 1);
    }

    return res;
}

void BFS(string A, string B)
{
    // 哈希表查询
    visited.insert(A);

    // 当前字符串和次数
    queue<pair<string, int>> q;

    // 如果初始相同
    if (A == B)
    {
        cout << 0;
        return;
    }

    // 初始入队
    q.push({A, 0});

    // 开始BFS
    while (!q.empty())
    {
        // 取出队头
        auto [s, step] = q.front();
        q.pop();

        // 如果找到了
        if (s == B)
        {
            cout << step;
            return;
        }

        // 次数超了则跳过
        if (step >= 10)
            continue;

        // 尝试所有变换规则
        for (auto [from, to] : rules)
        {
            // 所有可能结果
            vector<string> nexts = getNext(s, from, to);

            // 所有替换结果都考虑入队
            for (string next : nexts)
            {
                // 如果这个字符串已经出现过，跳过
                if (visited.count(next))
                    continue;

                // 标记已访问，并入队，步数 +1
                visited.insert(next);
                q.push({next, step + 1});
            }
        }
    }

    // 没找到
    cout << "NO ANSWER!";
}

int main()
{
    // 源和目标
    string A, B;
    cin >> A >> B;

    string a, b;

    // 读入规则from-to
    while (cin >> a >> b)
    {
        rules.push_back({a, b});
    }

    // BFS
    BFS(A, B);

    return 0;
}