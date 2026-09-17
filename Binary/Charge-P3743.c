/*
 * P3743 小鸟的设备
 * 难度:一般，依旧有前面的基础
 * 关键点：逆向。二分。贪心
 * 核心思路：由于切换不需要时间且初始电量均大于1，关心消耗量和充电量关系即可，然后假设一个时间并二分验证
 * 坑点：输出格式，.10lf
 */

#include <stdio.h>
#include <stdlib.h> //qsort

typedef struct
{
    double a; // 耗电
    double b; // 初始电量
} M;

// 检查当前时间是否合法
int Check(M m[], double mid, int n, double p)
{
    double max = p * mid;
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        double c = m[i].a * mid - m[i].b;
        // 直接求总和并比较
        sum += c > 0 ? c : 0;
        if (sum > max)
            return 0;
    }
    return 1;
}

int main()
{
    int n;
    double p;
    M m[100005];
    scanf("%d %lf", &n, &p);

    double A = 0; // 总耗电量
    double B = 0; // 总初始电量
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &m[i].a, &m[i].b);
        A += m[i].a;
        B += m[i].b;
    }

    // 如果充电不小于总耗电
    if (A <= p)
    {
        printf("-1\n");
        return 0;
    }

    // 二分尝试
    double right = B / (A - p);
    double left = 0;
    double maxTime = 0; // 当前最大时间
    for (int i = 0; i < 100; i++)
    {
        double mid = (right + left) / 2;
        // 合法说明少了，加水！！！
        if (Check(m, mid, n, p))
        {
            if (mid > maxTime)
                maxTime = mid;
            left = mid;
        }
        // 减水！！！
        else
        {
            right = mid;
        }
    }

    // 确保输出格式
    printf("%.10lf", maxTime);

    return 0;
}