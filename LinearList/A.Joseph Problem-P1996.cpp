/*
 * P1996 约瑟夫问题
 * 难度：简单
 * 关键点：队列模拟
 * 核心思路：
 *   把 1~n 依次入队，模拟报数过程。
 *   每次从队头取出一个人，报数 id++。
 *   如果 id == m，说明这个人出圈，输出他，并重置 id = 0；
 *   否则把他重新入队，等待下一轮。
 *   重复直到队列为空。
 * 坑点：
 *   1. 出圈后 id 要重置为 0，而不是 1；
 *   2. 出圈的人不再入队；
 *   3. 输出格式：每个数后面一个空格，行末空格一般不影响判题；
 *   4. 队列为空时循环结束。
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    queue<int> p;

    // 初始入队
    for (int i = 0; i < n; i++)
    {
        p.push(i + 1);
    }

    // 出队直到队空
    int id = 0;
    while (!p.empty())
    {
        // 记录并出队
        int tmp = p.front();
        p.pop();

        // 报号
        id++;

        // 如果是第m个，则不重新入队，并输出
        if (id == m)
        {
            cout << tmp << ' ';
            id = 0;
            continue;
        }

        // 重新入队
        p.push(tmp);
    }

    return 0;
}