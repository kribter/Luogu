/*
 * P5019 [NOIP 2018 提高组] 铺设道路
 * 难度：一般，想到简洁的贪心算法有点难
 * 关键点：贪心
 * 核心思路：把“区间操作”拆解成“相邻位置的高度差”，用局部增量代替全局模拟。
 * 坑点：无
 */
#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int prev, curr;
    scanf("%d", &prev); // 读第一个数
    long long ans = prev;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &curr);
        if (curr > prev)
            ans += curr - prev;
        prev = curr;
    }
    printf("%lld\n", ans);
    return 0;
}

// 第一次自己写的，再进一步就是简洁的贪心了
// 核心思路：单调不减/不增序列中最大值之和减去共用项
/*
#include <stdio.h>
#include <stdlib.h> //qsort

int main()
{
   int road[100000] = {0};
   int n;
   scanf("%d", &n);

   // 获得序列
   for (int i = 0; i < n; i++)
   {
       scanf("%d", &road[i]);
   }

   // 标记 1不减 -1不增
   int flag = 1;
   int max = 0;   // 序列最大值
   int share = 0; // 共用项
   int ans = 0;   // 结果
   for (int i = 0; i < n; i++)
   {
       if (max < road[i])
       {
           max = road[i];
       }

       // 增减性改变
       if ((road[i + 1] > road[i] && flag == -1) || (road[i + 1] < road[i] && flag == 1))
       {
           share = road[i];
           if (road[i + 1] > road[i])
           {
               // 不减变递增
               flag = 1;
           }
           else
           {
               // 不增变递减
               flag = -1;
           }

           i--;
           ans += max;
           ans -= share;
           max = 0;
       }
   }
   ans += max;

   printf("%d", ans);

   return 0;
}
*/
