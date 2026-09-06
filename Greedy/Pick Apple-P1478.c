/*
 * P1478 陶陶摘苹果（升级版）
 * 难度：易
 * 关键点：贪心
 * 核心思路：筛选能够到的，排序，贪心
 * 坑点：特殊情况-cnt=0等
 */

#include <stdio.h>
#include <stdlib.h> //qsort
int cmp(const void *a, const void *b);

int main()
{
    int n, s; // 个数 力气
    int a, b;
    scanf("%d %d %d %d", &n, &s, &a, &b);
    int max = a + b;
    int apples[5000];

    // 保留够得到的
    int x, y;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &x, &y);
        if (x <= max)
        {
            apples[cnt++] = y;
        }
    }

    // 排序
    qsort(apples, cnt, sizeof(int), cmp);

    // 采摘
    int total = 0;
    while (cnt > total && s >= apples[total])
    {
        s -= apples[total];
        // printf("%d ", apples[total]);
        total++;
    }
    printf("%d", total);

    return 0;
}

int cmp(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;

    // 递增
    return *pa - *pb;
}