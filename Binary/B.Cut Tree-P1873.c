/*
 * P1873 [COCI 2011/2012 #5] EKO / 砍树
 * 难度：一般
 * 关键点：二分
 * 核心思路：把最高树作为right，0作为left，直接二分就好了
 * 坑点：数据范围！！！以及二分真的挺快的，不用太担心时间复杂度吧。。。
 */

#include <stdio.h>
#include <stdlib.h> //qsort

int cmp(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;

    // 递减
    return *pb - *pa;
}

int main()
{
    int trees[1000005];
    int n, m;

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &trees[i]);
    }
    qsort(trees, n, sizeof(int), cmp);

    // 确定范围
    int left = 0, right = trees[0];
    int ans = 0;

    // 直接二分
    while (left <= right)
    {
        int mid = (left + right) / 2;
        long long sum = 0;
        for (int i = 0; i < n && trees[i] >= mid; i++)
        {
            sum += (trees[i] - mid);
        }

        if (sum >= m)
        {
            ans = mid;      // 可行，记录
            left = mid + 1; // 尝试更高
        }
        else
        {
            right = mid - 1; // 木材不够，降低高度
        }
    }

    printf("%d", ans);

    return 0;
}
