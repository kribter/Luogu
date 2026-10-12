/*
 * P1827 [USACO3.4] 美国血统 American Heritage
 * 难度：一般
 * 关键点：树的遍历关系
 * 核心思路：
 *   前序 = 根 + 左 + 右
 *   中序 = 左 + 根 + 右。
 *   注意到剩下的右节点的起始位置是一样的
 *   前序第一个是根，用它在中序中定位 pos，分出左右子树：
 *     左子树大小 = pos
 *     前序左 = pre.substr(1, pos)      中序左 = in.substr(0, pos)
 *     前序右 = pre.substr(pos + 1)     中序右 = in.substr(pos + 1)
 *   递归左右子树，最后输出根，即后序：左 + 右 + 根。
 * 坑点：
 *   1. substr(start, len) 第二个参数是长度，不是结束下标；
 *   2. in.substr(0, pos) 取左子树，不包括根。
 */

#include <bits/stdc++.h>
using namespace std;

void behind(string pre, string in)
{
    // 为空则结束
    if (pre.empty())
        return;

    // 根节点
    char root = pre[0];

    // 左子树+根节点位置（剩下的就都是右子树了）
    int pos = in.find(root);

    // 前序左子树
    string preL = pre.substr(1, pos);
    // 前序右子树
    string preR = pre.substr(pos + 1);

    // 中序左子树,sub的第一个参数是开始位置，第二个参数是取多少个！！！
    string inL = in.substr(0, pos);
    // 中序右子树
    string inR = in.substr(pos + 1);

    // 左子树
    behind(preL, inL);

    // 右子树
    behind(preR, inR);

    // 输出根节点
    cout << root;
}

int main()
{
    // 中序
    string in;

    // 前序
    string pre;

    // 处理输入
    cin >> in >> pre;

    // 开始后序遍历：左 右 中
    behind(pre, in);

    return 0;
}