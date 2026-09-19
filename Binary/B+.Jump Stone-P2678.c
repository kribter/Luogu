/*
 * P2678 [NOIP 2015 提高组] 跳石头
 * 难度：难，没有想到逆向思维
 * 关键点：二分，贪心，逆向
 * 核心思路：假设maxd是d，然后检测d满不满足条件，然后更新maxd，继续二分；而不是想着直接得出答案
 * 坑点：最后一块石头到终点的距离不够时，如果还有移动石头数量，可以把最后一块石头移走，而不是认为不合法
 */

#include <stdio.h>
#include <stdlib.h> //qsort

// 检查d是否满足条件
int Check(int stone[], int d, int n, int m)
{
    int last = 0;
    for (int i = 0; i < n; i++)
    {
        // 距离不够就移走
        if (stone[i] - last < d)
        {
            m--;
            // 用超了直接返回
            if (m < 0)
                return 0;
        }
        else
            last = stone[i];
    }

    // 距离不够，尝试是否能把最后一块石头移走
    if (stone[n] - last < d && m <= 0)
        return 0;

    return 1;
}

int main()
{
    int l, n, m;
    int stone[50005];
    scanf("%d %d %d", &l, &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &stone[i]);
    }
    stone[n] = l;

    // 二分
    int left = 0, right = l;
    int maxd = 0; // 记录当前最大d
    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (Check(stone, mid, n, m))
        {
            left = mid + 1;
            if (mid > maxd)
                maxd = mid;
        }
        else
        {
            right = mid - 1;
        }
    }

    printf("%d", maxd);

    return 0;
}