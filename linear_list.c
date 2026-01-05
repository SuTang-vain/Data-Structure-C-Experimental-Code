#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

//定义
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//初始化链表
LinkList InitList() {
    LinkList L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    return L;
}

//遍历+打印链表
void DisplayList(LinkList L) {
    printf("当前列表为：");
    LNode *p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//插入
int ListInsert(LinkList L, int pos, ElemType e) {
    LNode *p = L;
    int j = 0;
    //查找前驱结点
    while (p && j < pos - 1) {
        p = p->next;
        j++;
    }

    if (!p)
        return 0;

    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    printf("在位置[%d]插入'%d'\n", pos, e);
    return 1;
}

//删除
int ListDelete(LinkList L, int pos, ElemType *e) {
    LNode *p = L;
    int j = 0;

    while (p && j < pos - 1) {
        p = p->next;
        j++;
    }

    if (!p->next)
        return 0;

    LNode *q = p->next;
    *e = q->data;
    p->next = q->next;
    free(q);
    printf("删除位置[%d]的'%d'\n", pos, *e);
    return 1;
}

int main() {
    LinkList L = InitList();
    DisplayList(L);
    ElemType e;
    int pos, choice;

    printf("1.插入 2.删除 3.显示 0.退出\n");
    while (scanf("%d", &choice), choice) {
        if (choice == 1) {
            scanf("%d %d", &pos, &e);
            ListInsert(L, pos, e);
        } else if (choice == 2) {
            scanf("%d", &pos);
            if (ListDelete(L, pos, &e))
                printf("%d\n", e);
        } else if (choice == 3) {
            DisplayList(L);
        }
    }

    LNode *p, *q;
    p = L;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    return 0;
}
