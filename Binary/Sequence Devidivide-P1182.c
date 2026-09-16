/*
 * P1182 数列分段 Section II
 * 难度：一般，和前面两道类似
 * 关键点：贪心，二分
 * 核心思路：依旧反过来，依旧假设，依旧用假设去尝试，依旧更新
 * 坑点：check部分各种情况的考虑
 */

#include <stdio.h>

int Check(int num[], int n, int m, int sum)
{
    int tmp = 0;
    for (int i = 0; i < n; i++)
    {
        // 超过了
        if (num[i] > sum)
            return 0;
        if (tmp + num[i] > sum)
        {
            // 更新
            tmp = 0;
            m--;
            if (m < 0)
            {
                return 0;
            }
        }
        tmp += num[i];
    }

    // 最后一段
    if (tmp > 0)
        m--;

    return m >= 0;
}

int main()
{
    int n, m;
    int num[100005];
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }

    // 二分
    int left = 0, right = 1000000000;
    int maxSum = 1000000000;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (Check(num, n, m, mid))
        {
            right = mid - 1;
            if (mid < maxSum)
                maxSum = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    printf("%d", maxSum);

    return 0;
}