/*
 * P3853 [TJOI2007] 路标设置
 * 难度：一般，有了上一题jump stone的经验
 * 关键点：二分，贪心，逆向
 * 核心思路：逆向，二分尝试距离并更新目前最小的最大距离，
 * 坑点：基本无
 */

#include <stdio.h>
#include <stdlib.h> //qsort

int Check(int sign[], int d, int n, int k)
{
    int last = 0;
    for (int i = 0; i < n + 1; i++)
    {
        // 添加路标直到满足
        while (sign[i] - last > d)
        {
            last += d;
            k--;
            // 可添加路标用完了
            if (k < 0)
                return 0;
        }

        // 更新last
        last = sign[i];
    }

    return 1;
}

int main()
{
    int l, n, k;
    int sign[100005];
    scanf("%d %d %d", &l, &n, &k);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &sign[i]);
    }
    sign[n] = l;

    // 二分
    int left = 0, right = l;
    int mind = l;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (Check(sign, mid, n, k))
        {
            right = mid - 1;
            if (mid < mind)
                mind = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    printf("%d", mind);

    return 0;
}