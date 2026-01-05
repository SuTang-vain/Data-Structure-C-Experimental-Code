#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 栈结构
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 队列结构
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

// 栈操作
void initStack(Stack *s) {
    s->top = -1;
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}
//入栈
int push(Stack *s, int value) {
    if (s->top >= MAX_SIZE - 1) {
        printf("栈已满!\n");
        return 0;
    }
    s->top = s->top + 1;
    s->data[s->top] = value;
    return 1;
}
//出栈
int pop(Stack *s, int *value) {
    if (isStackEmpty(s)) {
        printf("栈为空!\n");
        return 0;
    }
    *value = s->data[s->top];
    s->top = s->top - 1;
    return 1;
}

// 队列操作
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isQueueEmpty(Queue *q) {
    return q->front == q->rear;
}
//入队
int enqueue(Queue *q, int value) {
    if ((q->rear + 1) % MAX_SIZE == q->front) {
        printf("队列已满!\n");
        return 0;
    }
    q->data[q->rear] = value;
    q->rear = q->rear + 1;
    q->rear = q->rear % MAX_SIZE;
    return 1;
}
//出队
int dequeue(Queue *q, int *value) {
    if (isQueueEmpty(q)) {
        printf("队列为空!\n");
        return 0;
    }
    *value = q->data[q->front];
    q->front = q->front + 1;
    q->front = q->front % MAX_SIZE;
    return 1;
}

void testStack() {
    Stack s;
    int choice, value;

    initStack(&s);
    printf("\n栈\n");

    while (1) {
        printf("1. 入栈\n2. 出栈\n3. 判栈空\n0. 返回\n");
        printf("请选择: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("请输入要入栈的值: ");
            scanf("%d", &value);
            if (push(&s, value)) {
                printf("入栈: %d\n", value);
            }
        } else if (choice == 2) {
            if (pop(&s, &value)) {
                printf("出栈: %d\n", value);
            }
        } else if (choice == 3) {
            if (isStackEmpty(&s)) {
                printf("栈为空\n");
            } else {
                printf("栈不为空\n");
            }
        } else if (choice == 0) {
            break;
        }
    }
}

void testQueue() {
    Queue q;
    int choice, value;

    initQueue(&q);
    printf("\n队列\n");

    while (1) {
        printf("1. 入队\n2. 出队\n3. 判队空\n0. 返回\n");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("请输入要入队的值: ");
            scanf("%d", &value);
            if (enqueue(&q, value)) {
                printf("入队: %d\n", value);
            }
        } else if (choice == 2) {
            if (dequeue(&q, &value)) {
                printf("出队: %d\n", value);
            }
        } else if (choice == 3) {
            if (isQueueEmpty(&q)) {
                printf("队列为空\n");
            } else {
                printf("队列不为空\n");
            }
        } else if (choice == 0) {
            break;
        }
    }
}

int main() {
    int choice;


    while (1) {
        printf("1. 栈\n");
        printf("2. 队列\n");
        printf("0. 退出\n");
        scanf("%d", &choice);

        if (choice == 1) {
            testStack();
        } else if (choice == 2) {
            testQueue();
        } else if (choice == 0) {
            break;
        }
    }

    return 0;
}
