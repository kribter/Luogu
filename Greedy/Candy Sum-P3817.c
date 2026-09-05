/*
 * P3817 小 A 的糖果
 * 难度：
 * 关键点：
 * 核心思路：优先减右边(i+1)的，因为修改num[i+1]不会影响num[i-1]+num[i]的和，不行再减左边的(i),这不会让sum变大
 * 坑点：
 */

#include <stdio.h>
#include <stdlib.h> //qsort

int main()
{
    int n, max;
    int num[100005] = {0};
    long long ans = 0;

    // 获得数据
    scanf("%d %d", &n, &max);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }

    // 调整到小于max
    int sum;
    for (int i = 0; i < n - 1; i++)
    {
        sum = num[i] + num[i + 1];
        if (sum > max)
        {
            int tmp = sum - max;
            // 优先减右边的
            if (num[i + 1] > tmp)
            {
                num[i + 1] -= tmp;
            }
            else
            {
                num[i] -= (tmp - num[i + 1]);
                num[i + 1] = 0;
            }
            ans += tmp;
        }
    }

    printf("%lld", ans);

    return 0;
}