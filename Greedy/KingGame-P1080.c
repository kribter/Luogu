/*
 * P1080 [NOIP 2012 提高组] 国王游戏
 * 难度：一般
 * 关键点：贪心，递归，数学证明
 * 核心思路：最后一个大臣获得的是 前面人左手积/自己的右手积=所有人左手积（固定的）/自己的双手积，
 *          所以只要找自己的双手积最大的放在最后，最后一个大臣得到的就是最少的，然后以此类推，可以得到整个序列，
 *          再去求最大的
 * 坑点：高精度！！！
 * 证明：见证明.md
 */

#include <stdio.h>
#include <stdlib.h> //qsort

typedef struct
{
    int l;
    int r;
    int ans;
} P;

int cmp(const void *a, const void *b)
{
    P *pa = (P *)a;
    P *pb = (P *)b;

    // 递增
    return pa->ans - pb->ans;
}

int main()
{
    int n;
    P king;
    P num[1005];

    scanf("%d", &n);
    scanf("%d %d", &king.l, &king.r);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &num[i].l, &num[i].r);
        num[i].ans = num[i].l * num[i].r;
    }

    // 排序，双手积递增
    qsort(num, n, sizeof(P), cmp);

    // 计算最大值
    int max = 0;
    long long ans = king.l;
    int tmp = 0;

    for (int i = 0; i < n; i++)
    {
        tmp = ans / num[i].r;
        if (tmp > max)
            max = tmp;
        ans *= num[i].l;
    }

    printf("%d", max);

    return 0;
}