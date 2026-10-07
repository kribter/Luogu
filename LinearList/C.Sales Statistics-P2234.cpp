/*
 * P2234 [HNOI2002] 营业额统计
 * 难度：普及/提高-
 * 关键点：排序 + 双向链表
 * 核心思路：
 *   把每天的营业额和原始下标一起排序，建双向链表。
 *   从最后一天倒着处理，当前节点的前驱和后继就是最接近值。
 *   处理完把当前节点从链表中删除，再往前处理。
 * 坑点：
 *   1. 用数组模拟链表，prev/next 存的是排序后的下标；
 *   2. 第 1 天直接加营业额，不需要比较；
 *   3. 结果可能超 int，用 long long。
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 32770;

struct Node
{
    int val;  // 营业额
    int id;   // 原始下标
    int prev; // 前驱在数组中的下标
    int next; // 后继在数组中的下标
} a[MAXN];

int pos[MAXN]; // pos[原始下标] = 排序后的位置

bool cmp(const Node &x, const Node &y)
{
    return x.val < y.val;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i].val);
        a[i].id = i;
    }

    // 按营业额排序
    sort(a + 1, a + n + 1, cmp);

    // 建双向链表
    for (int i = 1; i <= n; i++)
    {
        a[i].prev = i - 1;
        a[i].next = i + 1;
        pos[a[i].id] = i; // 记录原始下标对应的排序后位置
    }
    a[1].prev = 0; // 0 表示空
    a[n].next = 0;

    long long ans = a[pos[1]].val; // 第 1 天直接加营业额

    // 从最后一天倒着处理
    for (int i = n; i >= 2; i--)
    {
        int p = pos[i]; // 第 i 天在排序数组中的位置

        int best = INT_MAX;
        if (a[p].prev != 0)
            best = min(best, a[p].val - a[a[p].prev].val); // 前驱
        if (a[p].next != 0)
            best = min(best, a[a[p].next].val - a[p].val); // 后继

        ans += best;

        // 从链表中删除 p
        if (a[p].prev != 0)
            a[a[p].prev].next = a[p].next;
        if (a[p].next != 0)
            a[a[p].next].prev = a[p].prev;
    }

    printf("%lld\n", ans);
    return 0;
}