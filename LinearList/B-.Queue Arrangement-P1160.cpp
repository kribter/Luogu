/*
 * P1160 队列安排
 * 难度：一般
 * 关键点：链表，迭代器
 * 核心思路：
 *   list + pos[] 存每个同学的迭代器，插入删除都 O(1)。
 *   插左边用 insert(pos[k], i)，插右边用 insert(next(pos[k]), i)。
 * 坑点：
 *   1. insert 是插在给定位置之前，插右边要 next；
 *   2. 删除用 removed[] 标记，防止重复删除迭代器失效。
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{

    // 入
    int n;
    cin >> n;
    list<int> q;
    list<int>::iterator pos[n + 1]; // pos[i] 指向同学 i 在链表中的位置,迭代器
    bool removed[n + 1] = {};       // 是否已被删除

    // 初始化
    q.push_back(1);
    pos[1] = q.begin();

    // 入链表
    for (int i = 2; i <= n; i++)
    {
        int id, op;
        cin >> id >> op;

        // 左边
        if (op == 0)
        {
            pos[i] = q.insert(pos[id], i);
        }
        // 右边
        else
        {
            pos[i] = q.insert(next(pos[id]), i);
        }
    }

    // 出
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        if (!removed[x])
        {
            q.erase(pos[x]);
            removed[x] = true;
        }
    }

    // 输出
    for (int x : q)
    {
        cout << x << ' ';
    }

    return 0;
}