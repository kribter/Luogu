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
