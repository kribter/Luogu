/*
 * P2404 自然数的拆分问题
 * 难度：简单
 * 关键点：DFS 回溯、非递减枚举
 * 核心思路：用全局数组 path 维护当前正在构造的拆分序列，
 *           每次从 last 开始枚举下一个数，保证序列非递减；
 *           sum == n 时输出 path 里的完整序列（至少两个数才算拆分）。
 * 坑点：
 *   1. 单个数字不算拆分，必须 len > 1 才输出，否则会多输出 n 本身；
 *   2. 不限制非递减会重复，比如 1+2+1 和 1+1+2；
 *   3. 循环上限写 n - sum，不是 n，否则会有无效搜索；
 *   4. 用全局变量改 nowSum 时，回溯忘了恢复就全错，推荐按值传递；
 *   5. path 数组用来记录当前路径，path[len] = i 写入，递归返回后
 *      下一轮循环会覆盖它，相当于隐式回溯；
 *   6. 输出格式最后一个数后不能有 '+'；
 *   7. last 初始传 1，不是 0；
 */

#include <bits/stdc++.h>
using namespace std;

// 维护加数
int path[8];

// 打印
void PrintPath(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << path[i];
        if (i + 1 < n)
            cout << '+';
        else
            cout << endl;
    }
}

// DFS
void DFS(int last, int nowSum, int Sum, int dep)
{
    if (nowSum == Sum)
    {
        // 至少两个数才打印
        if (dep > 1)
            PrintPath(dep);
        return;
    }

    for (int i = last; i <= Sum - nowSum; i++)
    {
        // 记录并往下
        path[dep] = i;
        DFS(i, nowSum + i, Sum, dep + 1);
    }
}

int main()
{
    int Sum;
    cin >> Sum;

    // last是1，因为i至少是1
    DFS(1, 0, Sum, 0);

    return 0;
}