/*
 * P1219 [USACO1.5] 八皇后 Checker Challenge
 * 难度：初见难，特别是数据结构的构建
 * 关键点：DFS，回溯，数据结构
 * 核心思路：一直往下走，走不通就回头；利用高度凝练的数据结构简化特别多操作
 * 坑点：数据结构的选择，基0和基1的转换
 * 杂谈:这个数据结构,这个DFS,太漂亮了.
 */

#include <stdio.h>
#include <stdlib.h> //qsort

int count = 0;
int n;
int pos[15];        // pos[i]=j表示第i行第j列
int col[15] = {0};  // 列占用
int dig1[30] = {0}; // 主对角线 row-col+n
int dig2[30] = {0}; // 副对角线 row+col

void Dfs(int row)
{
    // 找完了
    if (row == n)
    {
        if (count < 3)
        {
            for (int i = 0; i < n; i++)
            {
                // 要注意答案是基1的，这里是基0的，要加1
                printf("%d ", pos[i] + 1);
            }
            printf("\n");
        }

        count++;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        // 如果这一列未占用 且 主对角线/副对角线上无其他
        if (!col[i] && !dig1[i - row + n] && !dig2[i + row])
        {
            // 添加
            pos[row] = i;

            // 更新
            col[i] = dig1[i - row + n] = dig2[i + row] = 1;

            // 往前
            Dfs(row + 1);

            // 回溯
            col[i] = dig1[i - row + n] = dig2[i + row] = 0;
        }
    }
}

int main()
{
    scanf("%d", &n);
    Dfs(0);
    printf("%d", count);

    return 0;
}