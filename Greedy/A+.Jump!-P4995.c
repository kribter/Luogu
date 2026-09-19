/*
 * P4995 跳跳！
 * 难度：易
 * 关键点：得到取得最大值方法，贪心
 * 核心思路：选目前路程最长的
 * 坑点：无
 */

#include <stdio.h>
#include <stdlib.h> //qsort

int cmp(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;

    // 递增
    return *pa - *pb;
}

int main()
{
    int n;
    scanf("%d", &n);
    int h[305];
    for (int i = 0; i < n; i++)
        scanf("%d", &h[i]);
    qsort(h, n, sizeof(int), cmp);

    long long ans = 0;
    int cur = 0;
    int l = 0, r = n - 1;
    for (int i = 0; i < n; i++)
    {
        // 选择与当前高度差更大的端点
        if (h[r] - cur > cur - h[l])
        {
            ans += (long long)(h[r] - cur) * (h[r] - cur);
            cur = h[r];
            r--;
        }
        else
        {
            ans += (long long)(h[l] - cur) * (h[l] - cur);
            cur = h[l];
            l++;
        }
    }
    printf("%lld\n", ans);
    return 0;
}