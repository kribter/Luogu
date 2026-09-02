/*
 * P1223 排队接水
 * 难度：易
 * 关键点：贪心，排序，数值大小估计
 * 核心思路：利用cmp排序，计算总等待时间并计算平均
 * 坑点：最坏情况下为5*10的九次方，int存不下；（floa）会损失精度导致四舍五入有误
 */

#include <stdio.h>
#include <stdlib.h> //qsort

typedef struct
{
    int t; // 时间
    int n; // 编号，注意实际情况是基1的！
} People;

int cmp(const void *a, const void *b)
{
    People *pa = (People *)a;
    People *pb = (People *)b;

    if (pa->t == pb->t)
        return pa->n - pb->n;
    else
        return pa->t - pb->t;
}

int main()
{
    int n;
    People people[1005];

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        // 获得时间与编号
        scanf("%d", &people[i].t);
        people[i].n = i + 1;
    }

    // 排序-递增
    qsort(people, n, sizeof(People), cmp);

    // 输出及计算平均值
    long total = 0; // 注意：int存不下最坏情况下5*10的九次方，要用long
    for (int i = 0; i < n; i++)
    {
        printf("%d ", people[i].n);
        total += (n - i - 1) * people[i].t;
    }
    printf("\n%.2f", (double)total / n); // 注意这里的（double），（floa）会损失精度导致四舍五入有误

    return 0;
}