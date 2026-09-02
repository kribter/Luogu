/*
 * P2240 【深基12.例1】部分背包问题
 * 难度：易
 * 关键点：排序。贪心，背包大小不足的处理
 * 核心思路：贪心，每次选密度最大的
 * 坑点：int/int得到的还是int，要进行（float）转换
 */

#include <stdio.h>
#include <stdlib.h> // qsort

typedef struct
{
    int v;
    int m;
    float p;
} Gold;

int cmp(const void *a, const void *b)
{
    Gold *pa = (Gold *)a;
    Gold *pb = (Gold *)b;

    return (pa->p < pb->p) - (pa->p > pb->p); // 相等
}

int main()
{
    Gold golds[100];
    int n, t;
    float v = 0;
    scanf("%d%d", &n, &t);

    for (int i = 0; i < n; i++)
    {
        // 计算密度
        scanf("%d %d", &golds[i].m, &golds[i].v);

        // 注意这里的float
        golds[i].p = (float)golds[i].v / golds[i].m;
    }

    // 排序
    qsort(golds, n, sizeof(Gold), cmp);

    // 贪心
    for (int i = 0; i < n && t > 0; i++)
    {
        if (t >= golds[i].m)
        {
            t -= golds[i].m;
            v += golds[i].v;
        }
        else
        {
            v += golds[i].p * t;
            t = 0;
        }
    }

    // 输出
    printf("%.2f", v);

    return 0;
}
