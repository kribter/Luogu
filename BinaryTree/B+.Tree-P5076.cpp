/*
 * P5076 【深基16.例7】普通二叉树（简化版）
 * 难度：难
 * 关键点：对树结构的了解
 * 核心思路：每个节点存 val、size（子树节点数）、左右孩子。
 *   排名查询：比 x 小的个数 + 1。
 *   按排名查询：看左子树大小决定往左、当前、往右。
 *   前驱：小于 x 的最大值；后继：大于 x 的最小值。
 * 坑点：
 *   1. 空树插入要 new 节点并让 head 指向它；
 *   2. 访问 q->left->size 前要判空；
 *   3. case 里声明变量要用花括号包住；
 */

#include <bits/stdc++.h>
using namespace std;

// 二叉树定义
// 都写在一个swtich里面了，看起来很烦
struct BST
{
    int val;
    int size;
    BST *left;
    BST *right;
};

void freeTree(BST *head)
{
    if (head == NULL)
        return;
    freeTree(head->left);
    freeTree(head->right);
    delete head;
}

int main()
{
    int n;
    cin >> n;

    // 空树
    BST *head = NULL;

    while (n--)
    {
        // 获得操作数和值
        int op, x;
        cin >> op >> x;

        BST *q;
        q = head;

        // 操作
        switch (op)
        {

        // 查询数 x 的排名
        case 1:
        {
            // 前面有多少个数
            int less = 0;

            // 下一个不为空就继续找
            while (q != NULL)
            {
                // 去往对应的子树
                if (q->val < x)
                {
                    // 排名增加
                    if (q->left != NULL)
                        less += (q->left->size + 1);
                    else
                        less += 1;

                    q = q->right;
                }
                else
                {
                    q = q->left;
                }
            }

            cout << less + 1 << '\n';
            break;
        }

        // 查询排名为 x(x≥1) 的数
        case 2:
        {

            // 排名不相同就一直找
            while (q != NULL)
            {
                int nowRank = 1;
                if (q->left != NULL)
                    nowRank += q->left->size;

                // 找到了
                if (x == nowRank)
                {
                    cout << q->val << '\n';
                    break;
                }

                else if (x < nowRank)
                {
                    q = q->left;
                }

                else
                {
                    q = q->right;
                    x -= nowRank;
                }
            }

            break;
        }
        // 求 x 的前驱
        case 3:
        {
            int ans = -2147483647;

            while (q != NULL)
            {
                if (q->val < x)
                {
                    ans = q->val;
                    q = q->right;
                }
                else
                {
                    q = q->left;
                }
            }

            cout << ans << '\n';
            break;
        }

        // 求 x 的后继
        case 4:
        {
            int ans = 2147483647;
            while (q != NULL)
            {
                if (q->val > x)
                {
                    ans = q->val;
                    q = q->left;
                }
                else
                {
                    q = q->right;
                }
            }
            cout << ans << '\n';
            break;
        }

        // 插入一个数 x
        case 5:
        {
            // 如果是空树
            if (head == NULL)
            {
                head = new BST;
                head->val = x;
                head->size = 1;
                head->left = NULL;
                head->right = NULL;

                // 操作结束
                break;
            }

            // 下一个不为空就继续找
            while (q != NULL)
            {
                // 新增节点，size增加
                q->size++;

                // 去往对应的子树
                if (x < q->val)
                {
                    // 如果是空的，就新建节点，后面填信息
                    if (q->left == NULL)
                    {
                        q->left = new BST;
                        q = q->left;
                        break;
                    }
                    q = q->left;
                }
                else
                {
                    if (q->right == NULL)
                    {
                        q->right = new BST;
                        q = q->right;
                        break;
                    }
                    q = q->right;
                }
            }

            // 找到合适的位置了,补充信息
            q->val = x;
            q->size = 1;
            q->left = q->right = NULL;

            break;
        }
        }
    }

    // 释放空间
    freeTree(head);

    return 0;
}

#pragma region 拆成函数写法，确实看起来会舒服一些
/*
// 子树大小，空节点为 0
int getSize(BST *p)
{
    return p == NULL ? 0 : p->size;
}

// 插入 x（调用方保证 x 不在集合中，head 传引用）
void insert(BST *&head, int x)
{
    if (head == NULL)
    {
        head = new BST;
        head->val = x;
        head->size = 1;
        head->left = head->right = NULL;
        return;
    }

    BST *q = head;
    while (q != NULL)
    {
        q->size++;
        if (x < q->val)
        {
            if (q->left == NULL) { q->left = new BST; q = q->left; break; }
            q = q->left;
        }
        else
        {
            if (q->right == NULL) { q->right = new BST; q = q->right; break; }
            q = q->right;
        }
    }
    q->val = x;
    q->size = 1;
    q->left = q->right = NULL;
}

// 操作 1：x 的排名
int getRank(BST *head, int x)
{
    int less = 0;
    BST *q = head;
    while (q != NULL)
    {
        if (q->val < x)
        {
            less += getSize(q->left) + 1;
            q = q->right;
        }
        else
        {
            q = q->left;
        }
    }
    return less + 1;
}

// 操作 2：排名为 x 的数
int getByRank(BST *head, int x)
{
    BST *q = head;
    while (q != NULL)
    {
        int L = getSize(q->left);
        if (x <= L)
            q = q->left;
        else if (x == L + 1)
            return q->val;
        else
        {
            x -= L + 1;
            q = q->right;
        }
    }
    return -1;   // 题目保证有解，不会到这里
}

// 操作 3：x 的前驱
int getPrev(BST *head, int x)
{
    int ans = -2147483647;
    BST *q = head;
    while (q != NULL)
    {
        if (q->val < x)
        {
            ans = q->val;
            q = q->right;
        }
        else
        {
            q = q->left;
        }
    }
    return ans;
}

// 操作 4：x 的后继
int getNext(BST *head, int x)
{
    int ans = 2147483647;
    BST *q = head;
    while (q != NULL)
    {
        if (q->val > x)
        {
            ans = q->val;
            q = q->left;
        }
        else
        {
            q = q->right;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    BST *head = NULL;

    while (n--)
    {
        int op, x;
        cin >> op >> x;

        switch (op)
        {
        case 1:
            cout << getRank(head, x) << '\n';
            break;
        case 2:
            cout << getByRank(head, x) << '\n';
            break;
        case 3:
            cout << getPrev(head, x) << '\n';
            break;
        case 4:
            cout << getNext(head, x) << '\n';
            break;
        case 5:
            insert(head, x);
            break;
        }
    }

    return 0;
}
*/
#pragma endregion