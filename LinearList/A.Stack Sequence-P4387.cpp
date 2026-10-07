/*
 * P4387 【深基15.习9】验证栈序列
 * 难度：一般
 * 关键点：栈模拟
 * 核心思路：
 *   按出栈序列逐个匹配。维护一个栈，按入栈序列顺序入栈，
 *   直到栈顶等于当前出栈元素，然后弹出。
 *   如果入栈序列用完仍无法匹配，则输出 No。
 * 坑点：
 *   1. 栈空时不能调用 top()；
 *   2. 入栈前检查 j < n，防止越界；
 *   3. 先读完整组数据，再统一判断，避免中途 break 影响输入。
 */

#include <bits/stdc++.h>
using namespace std;

int pushed[100005];
int poped[100005];

// 检查函数
bool check(int n)
{
    stack<int> st;
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        int x = poped[i];

        // 不断入栈，直到栈顶等于 x
        while (st.empty() || st.top() != x)
        {
            if (j >= n)
                return false; // 入栈序列用完
            st.push(pushed[j++]);
        }

        st.pop(); // 匹配成功，弹出
    }

    return true;
}

int main()
{
    // 输入加速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    while (q--)
    {
        int n;
        cin >> n;

        // 处理输入
        for (int i = 0; i < n; i++)
            cin >> pushed[i];
        for (int i = 0; i < n; i++)
            cin >> poped[i];

        cout << (check(n) ? "Yes" : "No") << '\n';
    }

    return 0;
}