/*
 * P2249 【深基13.例1】查找
 * 难度：易
 * 关键点：二分
 * 核心思路：找到后继续二分，而不是继续线性向前
 * 坑点：基0和基1的转换
 */

#include <stdio.h>

int num[1000005];

void Search(int n, int len)
{
    int left = 0, right = len - 1, ans = -2; // 因为后面会+1

    while (left <= right)
    {
        int mid = (left + right) / 2;
        // 如果找到了
        if (num[mid] == n)
        {
            // 继续往左找，二分
            ans = mid;
            right = mid - 1;
        }
        // 否则二分 这里加一减一是为了区间严格缩小
        else if (num[mid] > n)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    //+1是因为从基0到基1
    printf("%d ", ans + 1);
    return;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }

    for (int i = 0; i < m; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        Search(tmp, n);
    }

    return 0;
}
