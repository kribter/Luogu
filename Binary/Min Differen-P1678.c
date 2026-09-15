/*
 * P1678 烦恼的高考志愿
 * 难度：一般，
 * 关键点：二分，right和left最后的位置
 * 核心思路：二分，求差
 * 坑点：边界情况（ right<0/left>=m）情况的处理
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
    int school[100000];
    int score;
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &school[i]);
    }
    qsort(school, m, sizeof(int), cmp);

    // 二分查找最近的位置并计算分数差
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        // 读一个找一个就好了，不用存起来
        scanf("%d", &score);
        int left = 0, right = m - 1;
        int mid;

        // 二分
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (school[mid] > score)
            {
                right = mid - 1;
            }
            else if (school[mid] < score)
            {
                left = mid + 1;
            }
            // 找到直接退出就好了
            else
            {
                break;
            }
        }

        // 如果没找到，最后的结果会是school[left]是第一个比它大的，right是第一个比他小的
        if (school[mid] != score)
        {
            int l = -1, r = -1;
            if (left < m)
                l = school[left] - score;
            if (right >= 0)
                r = score - school[right];

            // 边界情况处理
            if (r == -1 || (l < r && l != -1))
                ans += l;
            else
                ans += r;
        }
    }

    printf("%lld", ans);

    return 0;
}
