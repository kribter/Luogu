/*
 * P4715 【深基16.例1】淘汰赛
 * 难度：一般
 * 关键点：二叉树抽象 / 整个比赛直接抽象
 * 核心思路：
 *   解法一（抽象）：亚军 = 决赛输的人 = 两个半区冠军中较弱的那个。
 *                   只需求左半区最大值和右半区最大值，取较小者输出编号。
 *   解法二（模拟）：把比赛建成完全二叉树，数组编号存储。
 *                   叶子放后半段存选手编号，内部节点存子树胜者编号，
 *                   从下往上两两合并，最后根的两个孩子中败者即亚军。
 * 坑点：
 *   1. 基 1，数组下标从 1 开始；
 *   2. 模拟解法树里存编号不存值，避免反查；
 *   3. 用 1 << n 不用 pow。
 */

#include <bits/stdc++.h>
using namespace std;

#pragma region 抽象解法
int main()
{
    int n;
    cin >> n;
    int num = 1 << n;

    // 参赛总人数
    vector<int> a(num + 1);
    for (int i = 1; i <= num; i++)
        cin >> a[i];

    // 找两个半区最大值
    int lmax = 0, lidx = 0;
    int rmax = 0, ridx = 0;
    for (int i = 1; i <= num / 2; i++)
    {
        if (a[i] > lmax)
        {
            lmax = a[i];
            lidx = i;
        }

        if (a[i + num / 2] > rmax)
        {
            rmax = a[i + num / 2];
            ridx = i + num / 2;
        }
    }

    // 输出亚军编号，既两个中较小的那一个
    cout << (lmax > rmax ? ridx : lidx);

    return 0;
}

#pragma endregion

#pragma region 二叉树模拟解法
/*int main()
{
    int n;
    cin >> n;
    int num = 1 << n;

    vector<int> val(num + 1);        // val[i]：选手 i 的实力值
    vector<int> winner(2 * num);     // winner[i]：子树 i 的胜者编号

    // 读入选手，叶子存编号
    for (int i = 1; i <= num; i++)
    {
        cin >> val[i];
        winner[num + i - 1] = i;
    }

    // 从下往上合并，i 是父节点编号
    for (int i = num - 1; i >= 1; i--)
    {
        int l = winner[2 * i];       // 左孩子胜者
        int r = winner[2 * i + 1];   // 右孩子胜者
        winner[i] = (val[l] > val[r]) ? l : r;
    }

    // 根的两个孩子：一个是冠军，另一个是亚军
    int l = winner[2];
    int r = winner[3];
    int ans = (val[l] > val[r]) ? r : l;

    cout << ans << '\n';
    return 0;
}*/
#pragma endregion