/*
 * P1102 A-B 数对
 * 难度：易
 * 关键点：二分
 * 核心思路：二分，先排序，然后用B+C确定A，去二分找A
 * 坑点：结果会超过int，要用long   =》使用参数的范围计算！！！
 */

#include <stdio.h>
#include <stdlib.h> //qsort

int num[200005];

int cmp(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;

    // 递增
    return *pa - *pb;
}

// 返回 target 在 num[0..len-1] 中第一次出现的位置，找不到返回 -1
int lowerBound(int target, int len)
{
    int left = 0, right = len - 1, ans = -1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (num[mid] >= target)
        {
            ans = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return ans;
}

// 返回 target 在 num[0..len-1] 中最后一次出现的位置，找不到返回 -1
int upperBound(int target, int len)
{
    int left = 0, right = len - 1, ans = -1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (num[mid] <= target)
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return ans;
}

// 二分查找并返回位置，没有就返回0
int Search(int n, int len)
{
    int left = 0, right = len - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        // 如果找到了
        if (num[mid] == n)
        {
            return upperBound(n, len) - lowerBound(n, len) + 1;
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

    return -1;
}

int main()
{
    int n, c;
    scanf("%d %d", &n, &c);

    // 输入并排序
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    qsort(num, n, sizeof(int), cmp);

    long ans = 0, tmp;
    for (int i = 0; i < n && num[i] + c <= num[n - 1]; i++)
    {
        tmp = Search(num[i] + c, n);
        if (tmp != -1)
        {
            ans += tmp;
        }
    }

    printf("%ld", ans);

    return 0;
}

/*不用二分的双指针解法

int main()
{
    int n, c;
    scanf("%d %d", &n, &c);
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    qsort(num, n, sizeof(int), cmp);

    long long ans = 0;
    int i = 0, j = 0;
    while (i < n)
    {
        // 统计当前 B 的重复次数
        int b = num[i];
        int cntB = 0;
        while (i < n && num[i] == b)
        {
            cntB++;
            i++;
        }
        // 移动 j 到第一个 >= b + c 的位置
        int target = b + c;
        while (j < n && num[j] < target)
            j++;
        if (j < n && num[j] == target)
        {
            // 统计 A 的重复次数
            int cntA = 0;
            int k = j;
            while (k < n && num[k] == target)
            {
                cntA++;
                k++;
            }
            ans += (long long)cntB * cntA;
        }
    }
    printf("%lld\n", ans);
    return 0;
}*/