/*
 * P4447 [AHOI2018初中组] 分组
 * 难度：难，没见过
 * 关键点：链表。贪心
 * 核心思路：分成若干个队列，每添加一个新成员就去找可以加入的队列中最短呃那一个
 * 坑点：链表节点创建时，若无后续节点，next要置空；链表用完后要free释放空间
 */

#include <stdio.h>
#include <stdlib.h> //qsort

typedef struct Node
{
    int len;           // 当前长度
    int end;           // 最后一个
    struct Node *next; // 下一个节点
} Node;

int cmp(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;

    // 递减
    return *pb - *pa;
}

void Add(int num, Node *head)
{
    // 如果链表是空的
    if (head->next == NULL)
    {
        // 创建新队列
        Node *new = (Node *)malloc(sizeof(Node));
        new->end = num;
        new->len = 1;
        head->next = new;
        new->next = NULL;
        return;
    }

    // 非空且找得到
    Node *q = head;
    while (q->next != NULL)
    {
        q = q->next;
        if (q->end - num == 1)
        {
            q->end--;
            q->len++;
            return;
        }
        else if (q->end - num > 1)
        {
            break;
        }
    }

    // 非空但找不到
    Node *new = (Node *)malloc(sizeof(Node));
    new->end = num;
    new->len = 1;
    new->next = head->next;
    head->next = new;

    // 由于链表的特性以及这里是头插法
    // 在前面的一定会是更新的队伍-队伍长度一定会更短
    // 或者end一定是更新的num

    return;
}

void freeList(Node *head)
{
    Node *p = head;
    while (p != NULL)
    {
        Node *tmp = p; // 先保存当前节点
        p = p->next;   // 再移动到下一个
        free(tmp);     // 释放当前节点
    }
}

int main()
{
    int num[100005];
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);

    // 递减序列
    qsort(num, n, sizeof(int), cmp);

    // 分组
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    for (int i = 0; i < n; i++)
        Add(num[i], head);

    // 找最小的
    Node *p = head;
    int min = head->next->len;
    while (p->next != NULL)
    {
        p = p->next;
        if (p->len < min)
            min = p->len;
    }
    printf("%d", min);

    freeList(head);

    return 0;
}
