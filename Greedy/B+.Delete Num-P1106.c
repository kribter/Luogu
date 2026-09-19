/*
 * P1106 删数问题
 * 难度：易
 * 关键点：贪心
 * 核心思路：删去k位后剩下的位数是固定的->由高到低每一位选择尽力小的数
 * 坑点：很多细节上的问题，参数的选择等等，多设置几个清楚的变量会清晰很多
 */

#include <stdio.h>
#include <stdlib.h> //qsort
#include <string.h>

int main()
{
    char num[250];
    int k;

    // 获得长度，并把n变成要留下的位数数
    scanf("%s %d", num, &k);
    int len = strlen(num);
    int need = len - k; // 需要保留的位数
    int pos[255];       // 存储每一位在原串中的下标
    int start = 0;      // 当前搜索起点

    // 选择尽量小
    for (int i = 0; i < need; i++)
    {
        int end = k + i; // 搜索终点（保证后面还能选够）
        int min = 10, min_pos = start;
        for (int j = start; j <= end; j++)
        {
            if (num[j] - '0' < min)
            {
                min = num[j] - '0';
                min_pos = j;
                if (min == 0)
                    break; // 0 是最小，提前结束
            }
        }
        // 更新数据
        pos[i] = min_pos;
        start = min_pos + 1;
    }

    // 输出，去掉前导零
    int flag = 0;
    for (int i = 0; i < need; i++)
    {
        char c = num[pos[i]];
        if (flag == 0 && c == '0')
            continue;
        printf("%c", c);
        flag = 1;
    }
    if (flag == 0)
        printf("0"); // 如果全部是0，输出一个0
    printf("\n");

    return 0;
}