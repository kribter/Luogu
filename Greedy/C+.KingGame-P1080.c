/*
 * P1080 [NOIP 2012 提高组] 国王游戏
 * 难度：难
 * 关键点：贪心，递归，数学证明
 * 核心思路：最后一个大臣获得的是 前面人左手积/自己的右手积=所有人左手积（固定的）/自己的双手积，
 *          所以只要找自己的双手积最大的放在最后，最后一个大臣得到的就是最少的，然后以此类推，可以得到整个序列，
 *          再去求最大的
 * 坑点：高精度！！！
 * 证明：见证明.md
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 5000 // 最大位数，足够存储 1000 个 10000 相乘的结果

// 大整数结构：digits[0] 是最低位
typedef struct
{
    int digits[MAXLEN];
    int len;
} BigInt;

// 初始化为整数值 val
void bigInit(BigInt *x, int val)
{
    x->len = 0;
    if (val == 0)
    {
        x->digits[0] = 0;
        x->len = 1;
        return;
    }
    while (val)
    {
        x->digits[x->len++] = val % 10;
        val /= 10;
    }
}

// 大整数乘以整数 val
void bigMul(BigInt *x, int val)
{
    int carry = 0;
    for (int i = 0; i < x->len; i++)
    {
        int prod = x->digits[i] * val + carry;
        x->digits[i] = prod % 10;
        carry = prod / 10;
    }
    while (carry)
    {
        x->digits[x->len++] = carry % 10;
        carry /= 10;
    }
}

// 大整数除以整数 val，结果存入 res
void bigDiv(BigInt *x, int val, BigInt *res)
{
    int rem = 0;
    res->len = 0;
    // 从最高位开始除
    for (int i = x->len - 1; i >= 0; i--)
    {
        int cur = rem * 10 + x->digits[i];
        res->digits[res->len++] = cur / val;
        rem = cur % val;
    }
    // 反转，使低位在前
    for (int i = 0; i < res->len / 2; i++)
    {
        int t = res->digits[i];
        res->digits[i] = res->digits[res->len - 1 - i];
        res->digits[res->len - 1 - i] = t;
    }
    // 去除末尾多余的零
    while (res->len > 1 && res->digits[res->len - 1] == 0)
        res->len--;
    if (res->len == 0)
    {
        res->len = 1;
        res->digits[0] = 0;
    }
}

// 比较两个大整数：a>b 返回 1，a<b 返回 -1，相等返回 0
int bigCmp(const BigInt *a, const BigInt *b)
{
    if (a->len != b->len)
        return a->len > b->len ? 1 : -1;
    for (int i = a->len - 1; i >= 0; i--)
    {
        if (a->digits[i] != b->digits[i])
            return a->digits[i] > b->digits[i] ? 1 : -1;
    }
    return 0;
}

// 输出大整数
void bigPrint(const BigInt *x)
{
    for (int i = x->len - 1; i >= 0; i--)
    {
        printf("%d", x->digits[i]);
    }
    printf("\n");
}

// 大臣结构
typedef struct
{
    int l;
    int r;
    long long ans; // l * r，用 long long 存储（最大 10^8）
} P;

// 按 l*r 递增排序
int cmp(const void *a, const void *b)
{
    P *pa = (P *)a;
    P *pb = (P *)b;
    if (pa->ans < pb->ans)
        return -1;
    if (pa->ans > pb->ans)
        return 1;
    return 0;
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
        num[i].ans = (long long)num[i].l * num[i].r;
    }

    // 贪心：按左右手乘积递增排序
    qsort(num, n, sizeof(P), cmp);

    BigInt cur, reward, maxReward;
    bigInit(&cur, king.l);  // 累计乘积初始为国王左手
    bigInit(&maxReward, 0); // 最大奖励初始为 0

    for (int i = 0; i < n; i++)
    {
        // 当前大臣的奖励 = 累计乘积 / 他的右手
        bigDiv(&cur, num[i].r, &reward);
        if (bigCmp(&reward, &maxReward) > 0)
        {
            maxReward = reward; // 更新最大奖励
        }
        // 累计乘积乘以当前大臣的左手
        bigMul(&cur, num[i].l);
    }

    bigPrint(&maxReward);
    return 0;
}