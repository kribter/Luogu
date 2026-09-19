/*
 * P2440 木材加工
 * 难度：易
 * 关键点：二分
 * 核心思路：直接二分，然后算总段数，大于就直接下一个二分并更新目前最长长度
 * 坑点：left不能=0，会有除0错误；胆子大一点直接二分+扫描复杂度就是 （log n *n）
 */

#include <stdio.h>
#include <stdlib.h> //qsort

int main()
{
    int n, k;
    int tree[100005];
    scanf("%d %d", &n, &k);
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tree[i]);
        // 记录最大长度
        if (max < tree[i])
            max = tree[i];
    }

    // 直接二分
    int left = 1, right = max;
    int ans;
    // 目前最长
    int len = 0;
    while (left <= right)
    {
        ans = 0;
        int mid = (left + right) / 2;

        // 统计总段数
        for (int i = 0; i < n; i++)
        {
            ans += tree[i] / mid;
            // 如果够了，多了还是刚刚好不重要
            if (ans >= k)
            {
                // 更新最长的
                if (mid > len)
                {
                    len = mid;
                }
                break;
            }
        }

        // 长了
        if (ans < k)
        {
            right = mid - 1;
        }
        // 短了
        else
        {
            left = mid + 1;
        }
    }

    printf("%d", len);

    return 0;
}
