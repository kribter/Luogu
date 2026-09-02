/*
 * P1803 凌乱的yyy / 线段覆盖
 * 难度：易
 * 关键点：贪心
 * 核心思路：安排结束最快的活动
 * 证明：分成两段，前面的那一段只有一个活动，如果存在一个比它结束快的，那把这个变成结束快的那个结果是一样的，还会多出更多时间
 * 坑点：无
 *
 * 其他：如果考虑空闲时间最少呢？结果还是一样的吗？
 * 变成其他问题了
 */

#include <stdio.h>
#include <stdlib.h> //qsort

// 活动结构体
typedef struct
{
    int start;
    int end;
} Act;

// 递减排序
int cmp(const void *a, const void *b)
{
    Act *pa = (Act *)a;
    Act *pb = (Act *)b;

    return pa->end - pb->end;
}

int main()
{
    // 初始化
    Act acts[1000000];
    int n;
    int end = 0; // 目前结束时间
    int sum = 0; // 目前参加活动数

    // 获得数据
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &acts[i].start, &acts[i].end);
    }

    // 排序:结束时间递减
    qsort(acts, n, sizeof(Act), cmp);

    // 排活动
    for (int i = 0; i < n; i++)
    {
        // 目前结束最快的活动能否开始
        if (acts[i].start >= end)
        {
            end = acts[i].end;
            sum++;
        }
    }

    // 输出
    printf("%d", sum);

    return 0;
}