#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct TreeNode {
    char data;
    struct TreeNode *lchild, *rchild;
} TreeNode;

// 创建二叉树
TreeNode* createTree() {
    char ch;
    scanf(" %c", &ch);
    if (ch == '#') return NULL;
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = ch;
    node->lchild = createTree();
    node->rchild = createTree();
    return node;
}

// 递归前序遍历
void preOrderRecursive(TreeNode* root) {
    if (!root) return;
    printf("%c ", root->data);
    preOrderRecursive(root->lchild);
    preOrderRecursive(root->rchild);
}

// 递归中序遍历
void inOrderRecursive(TreeNode* root) {
    if (!root) return;
    inOrderRecursive(root->lchild);
    printf("%c ", root->data);
    inOrderRecursive(root->rchild);
}

// 递归后序遍历
void postOrderRecursive(TreeNode* root) {
    if (!root) return;
    postOrderRecursive(root->lchild);
    postOrderRecursive(root->rchild);
    printf("%c ", root->data);
}

// 查找节点
TreeNode* search(TreeNode* root, char key) {
    if (!root || root->data == key) return root;
    if (key < root->data)
        return search(root->lchild, key);
    else
        return search(root->rchild, key);
}

// 插入节点
TreeNode* insert(TreeNode* root, char key) {
    if (!root) {
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        node->data = key;
        node->lchild = node->rchild = NULL;
        return node;
    }
    if (key < root->data)
        root->lchild = insert(root->lchild, key);
    else if (key > root->data)
        root->rchild = insert(root->rchild, key);
    return root;
}

// 查找最小节点
TreeNode* findMin(TreeNode* root) {
    while (root && root->lchild)
        root = root->lchild;
    return root;
}

// 删除节点
TreeNode* deleteNode(TreeNode* root, char key) {
    if (!root) return NULL;

    if (key < root->data)
        root->lchild = deleteNode(root->lchild, key);
    else if (key > root->data)
        root->rchild = deleteNode(root->rchild, key);
    else {
        if (!root->lchild) {
            TreeNode* temp = root->rchild;
            free(root);
            return temp;
        } else if (!root->rchild) {
            TreeNode* temp = root->lchild;
            free(root);
            return temp;
        }
        TreeNode* temp = findMin(root->rchild);
        root->data = temp->data;
        root->rchild = deleteNode(root->rchild, temp->data);
    }
    return root;
}

// 非递归前序遍历
void preOrderIterative(TreeNode* root) {
    if (!root) return;
    TreeNode* stack[MAX];
    int top = 0;
    stack[top++] = root;
    while (top) {
        TreeNode* node = stack[--top];
        printf("%c ", node->data);
        if (node->rchild) stack[top++] = node->rchild;
        if (node->lchild) stack[top++] = node->lchild;
    }
}

// 非递归中序遍历
void inOrderIterative(TreeNode* root) {
    TreeNode* stack[MAX];
    int top = 0;
    TreeNode* curr = root;
    while (top || curr) {
        while (curr) {
            stack[top++] = curr;
            curr = curr->lchild;
        }
        curr = stack[--top];
        printf("%c ", curr->data);
        curr = curr->rchild;
    }
}

// 后序遍历用的栈元素
typedef struct { TreeNode* node; int visited; } Item;

// 非递归后序遍历
void postOrderIterative(TreeNode* root) {
    if (!root) return;
    Item stack[MAX];
    int top = 0;
    stack[top++] = (Item){root, 0};
    while (top) {
        Item cur = stack[--top];
        if (!cur.node) continue;
        if (cur.visited) {
            printf("%c ", cur.node->data);
        } else {
            stack[top++] = (Item){cur.node, 1};
            if (cur.node->rchild) stack[top++] = (Item){cur.node->rchild, 0};
            if (cur.node->lchild) stack[top++] = (Item){cur.node->lchild, 0};
        }
    }
}

void printMenu() {
    printf("1. 重新创建二叉树\n");
    printf("2. 递归前序遍历\n");
    printf("3. 递归中序遍历\n");
    printf("4. 递归后序遍历\n");
    printf("5. 非递归前序遍历\n");
    printf("6. 非递归中序遍历\n");
    printf("7. 非递归后序遍历\n");
    printf("8. 查找节点\n");
    printf("9. 插入节点\n");
    printf("10. 删除节点\n");
    printf("0. 退出\n");
}

int main() {
    TreeNode* root = NULL;
    int choice;
    char key;

    printf("二叉树创建\n");
    root = createTree();

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n重新创建二叉树\n");
                printf("请输入: ");
                root = createTree();
                break;
            case 2:
                printf("\n递归前序遍历结果: ");
                preOrderRecursive(root);
                printf("\n");
                break;
            case 3:
                printf("\n递归中序遍历结果: ");
                inOrderRecursive(root);
                printf("\n");
                break;
            case 4:
                printf("\n递归后序遍历结果: ");
                postOrderRecursive(root);
                printf("\n");
                break;
            case 5:
                printf("\n非递归前序遍历结果: ");
                preOrderIterative(root);
                printf("\n");
                break;
            case 6:
                printf("\n非递归中序遍历结果: ");
                inOrderIterative(root);
                printf("\n");
                break;
            case 7:
                printf("\n非递归后序遍历结果: ");
                postOrderIterative(root);
                printf("\n");
                break;
            case 8:
                printf("\n请输入要查找的节点值: ");
                scanf(" %c", &key);
                TreeNode* result = search(root, key);
                if (result)
                    printf("找到节点: %c\n", result->data);
                else
                    printf("未找到节点: %c\n", key);
                break;
            case 9:
                printf("\n请输入要插入的节点值: ");
                scanf(" %c", &key);
                root = insert(root, key);
                printf("节点 %c 已插入\n", key);
                printf("中序遍历结果: ");
                inOrderRecursive(root);
                printf("\n");
                break;
            case 10:
                printf("\n请输入要删除的节点值: ");
                scanf(" %c", &key);
                root = deleteNode(root, key);
                printf("节点 %c 已删除\n", key);
                printf("中序遍历结果: ");
                inOrderRecursive(root);
                printf("\n");
                break;
            case 0:
                printf("退出程序。\n");
                break;
            default:
                printf("无效选择！\n");
        }
    } while (choice != 0);

    return 0;
}
