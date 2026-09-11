/*
 * P1012 [NOIP 1998 提高组] 拼数
 * 难度：一般
 * 关键点：贪心，字符串排序
 * 核心思路：让ab=sa+sb，ba=sb+sa，比较ab和ba就知道sa和sb谁在前了
 * 坑点：cmo排序
 */

#include <stdio.h>
#include <stdlib.h> //qsort
#include <string.h> //字符串

int cmp(const void *a, const void *b)
{
    const char *sa = (const char *)a;
    const char *sb = (const char *)b;
    char ab[100], ba[100];

    // ab=sa+sb
    strcpy(ab, sa);
    strcat(ab, sb);

    // ba=sb+sa
    strcpy(ba, sb);
    strcat(ba, sa);

    // 注意：降序，所以用 ba 和 ab 比较
    return strcmp(ba, ab);
}

int main()
{
    int n;
    scanf("%d", &n);

    char nums[25][15]; // n ≤ 20，每个数字最多 10 位
    for (int i = 0; i < n; i++)
    {
        scanf("%s", nums[i]);
    }

    // 排序
    qsort(nums, n, sizeof(nums[0]), cmp);

    // 输出
    for (int i = 0; i < n; i++)
    {
        printf("%s", nums[i]);
    }
    printf("\n");

    return 0;
}
