/*
 * P2392 kkksc03 考前临时抱佛脚
 * 难度：初见难
 * 关键点：DP
 * 核心思路：分成两半，去找一遍不超过一半的最大值
 * 坑点：dp[0]要置1
 */

#include <stdio.h>
#include <string.h>

int solve(int m, int arr[])
{
    int sum = 0;
    for (int i = 0; i < m; i++)
        sum += arr[i];

    // 最理想情况下
    int half = sum / 2;

    // DP初始化
    int dp[605] = {0};
    dp[0] = 1;

    for (int i = 0; i < m; i++)
    {
        // 逆序防止重复添加
        for (int j = half; j >= arr[i]; j--)
        {
            // 找到上一个
            if (dp[j - arr[i]])
                dp[j] = 1;
        }
    }

    // 找到少的那边的最大值
    while (!dp[half])
        half--;

    // 结果是多的那一边
    return sum - half;
}

int main()
{
    int s[4], arr[25];
    scanf("%d %d %d %d", &s[0], &s[1], &s[2], &s[3]);
    int ans = 0;

    // 一共4科
    for (int k = 0; k < 4; k++)
    {
        // 处理1科
        for (int i = 0; i < s[k]; i++)
            scanf("%d", &arr[i]);
        ans += solve(s[k], arr);
    }

    printf("%d\n", ans);

    return 0;
}