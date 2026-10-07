/*
 * P1241 括号序列
 * 难度：一般
 * 关键点：栈、标记数组
 * 核心思路：
 *   用栈存未匹配左括号的下标，遇到右括号时看栈顶是否匹配。
 *   匹配成功则标记 matched[i] 和 matched[栈顶] 为 true，弹出栈顶。
 *   最后遍历原串：已匹配原样输出，未匹配补上另一半。
 * 坑点：
 *   1. matched[] 必须初始化为 false；
 *   2. 栈空时不能调用 st.top()，要先判断 !st.empty()；
 *   3. 未匹配的右括号补左括号，未匹配的左括号补右括号。
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    // 处理输入
    string s;

    // 处理配对
    stack<int> st;

    // 记录配对信息
    bool matched[105] = {};

    cin >> s;
    // 逐字符处理
    for (int i = 0; i < (int)s.length(); i++)
    {
        // 入栈
        if (s[i] == '(' || s[i] == '[')
        {
            st.push(i);
        }
        else if (s[i] == ')')
        {
            // 配对成功
            if (!st.empty() && s[st.top()] == '(')
            {
                matched[st.top()] = true;
                matched[i] = true;
                // 弹出
                st.pop();
            }
        }
        else if (s[i] == ']')
        {
            // 配对成功
            if (!st.empty() && s[st.top()] == '[')
            {
                matched[st.top()] = true;
                matched[i] = true;
                // 弹出
                st.pop();
            }
        }
    }

    // 输出
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (matched[i])
        {
            cout << s[i]; // 已匹配，原样输出
        }
        else
        {
            if (s[i] == '(')
                cout << "()";
            else if (s[i] == '[')
                cout << "[]";
            else if (s[i] == ')')
                cout << "()";
            else if (s[i] == ']')
                cout << "[]";
        }
    }

    return 0;
}