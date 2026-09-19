/*
 * P1090 [NOIP 2004 提高组] 合并果子
 * 难度：难，链表的使用比较陌生
 * 关键点：链表
 * 核心思路：两个最低的合成，变成一个新的，然后循环
 * 坑点：链表的使用，要先检查是否为空再用
 */

/*不可能每次合并之后再排序，这样时间复杂度会很大吧，虽然这样确实是最直接的想法
1.注意到an的取值最大是20000，可以直接建立一个这样大小的数组吗？
不行，因为中间和会很大，导致数组存不下！

2. 用链表吧，每次读取前两个，然后把新的放回去？
*/

#include <stdio.h>
#include <stdlib.h> //qsort

typedef struct P
{
    int w;
    struct P *next;
} P;

// 递增添加新元素
void Add(int w, P *head)
{
    P *q = head;
    // 找到第一个 w 大于等于当前值的位置，或走到链表尾
    while (q->next != NULL && q->next->w < w)
    {
        q = q->next;
    }

    // 创建新节点并插入
    P *newNode = (P *)malloc(sizeof(P));
    newNode->w = w;
    newNode->next = q->next;
    q->next = newNode;
}

int Conbine(P *head)
{
    int ans = 0;
    int tmp = 0;
    P *q = head->next;
    while (q != NULL && q->next != NULL)
    {
        // 求新节点值
        tmp = q->w + q->next->w;
        ans += tmp;

        // 更新链表
        head->next = q->next->next;
        Add(tmp, head);
        q = head->next;

        tmp = 0;
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);

    P *head = (P *)malloc(sizeof(P)); // 创建头结点
    head->next = NULL;
    int tmp;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tmp);
        Add(tmp, head);
    }

    printf("%d", Conbine(head));

    return 0;
}