#include <stdio.h>
#include <stdlib.h>

typedef struct { int u, v; } Edge;

int n, m;
Edge edges[100];
int vis[100], q[100];

int adj(int from, int to) {
    for (int i = 0; i < m; i++)
        if ((edges[i].u == from && edges[i].v == to) ||
            (edges[i].u == to && edges[i].v == from))
            return 1;
    return 0;
}

void dfs(int u) {
    vis[u] = 1; printf("%d ", u);
    for (int i = 0; i < n; i++)
        if (adj(u, i) && !vis[i]) dfs(i);
}

void bfs(int s) {
    int f = 0, r = 0;

    vis[s] = 1; 
    q[r++] = s;
    
    while (f < r) {
        int u = q[f++];
        printf("%d ", u);

        for (int i = 0; i < n; i++)
            if (adj(u, i) && !vis[i]) { 
                vis[i] = 1; 
                q[r++] = i; }
    }
}

void print_edges() {
    printf("当前边列表 (%d条):\n", m);
    for (int i = 0; i < m; i++)
        printf("  %d: (%d, %d)\n", i, edges[i].u, edges[i].v);
}

void add_edge() {
    int a, b;
    printf("输入要添加的边 (u v): ");
    scanf("%d %d", &a, &b);
    if (a < 0 || a >= n || b < 0 || b >= n) {
        printf("错误\n");
        return;
    }
    if (adj(a, b)) {
        printf("边已存在\n");
        return;
    }
    edges[m].u = a;
    edges[m].v = b;
    m++;
    printf("添加成功\n");
}

void delete_edge() {
    int a, b;
    printf("输入要删除的边 (u v): ");
    scanf("%d %d", &a, &b);
    for (int i = 0; i < m; i++) {
        if ((edges[i].u == a && edges[i].v == b) ||
            (edges[i].u == b && edges[i].v == a)) {
            edges[i] = edges[m - 1];
            m--;
            printf("删除成功\n");
            return;
        }
    }
    printf("边不存在\n");
}

void find_edge() {
    int a, b;
    printf("输入要查找的边 (u v): ");
    scanf("%d %d", &a, &b);
    if (adj(a, b))
        printf("边 (%d, %d) 存在\n", a, b);
    else
        printf("边 (%d, %d) 不存在\n", a, b);
}

void menu() {
    printf("\n图操作\n");
    printf("1. 添加边\n");
    printf("2. 删除边\n");
    printf("3. 查找边\n");
    printf("4. 显示所有边\n");
    printf("5. DFS遍历\n");
    printf("6. BFS遍历\n");
    printf("0. 退出\n");
}

int main() {
    printf("顶点数: "); scanf("%d", &n);
    printf("边数: "); scanf("%d", &m);
    for (int i = 0; i < m; i++)
        scanf("%d %d", &edges[i].u, &edges[i].v);

    while (1) {
        menu();
        int op;
        printf("选择操作: ");
        scanf("%d", &op);
        if (op == 0) break;
        switch (op) {
            case 1: add_edge(); break;
            case 2: delete_edge(); break;
            case 3: find_edge(); break;
            case 4: print_edges(); break;
            case 5:
                for (int i = 0; i < n; i++) vis[i] = 0;
                printf("DFS: "); dfs(0); printf("\n"); break;
            case 6:
                for (int i = 0; i < n; i++) vis[i] = 0;
                printf("BFS: "); bfs(0); printf("\n"); break;
        }
    }
    return 0;
}
