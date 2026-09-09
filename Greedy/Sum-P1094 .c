/*
 * P1094 [NOIP 2007 普及组] 纪念品分组
 * 难度：易
 * 关键点：贪心，双指针
 * 核心思路：排完序双指针配对
 * 坑点：双指针用while，用for容易出问题紊乱
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
    int max, n;
    scanf("%d %d", &max, &n);
    int v[30005];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

    qsort(v, n, sizeof(int), cmp);

    int ans = 0;
    int left = 0, right = n - 1;
    while (left <= right)
    {
        if (v[left] + v[right] <= max)
        {
            left++;
        }
        right--;
        ans++;
    }

    printf("%d", ans);

    return 0;
}
