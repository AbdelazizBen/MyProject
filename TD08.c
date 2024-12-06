#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
int factorial_recursive(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial_recursive(n - 1);
}
int factorial_iterative(int n) {
    int stack[100];  
    int top = -1;
    int result = 1;  
    while (n > 0) {
        stack[++top] = n--;
    }
    while (top >= 0) {
        result *= stack[top--];
    }
    return result;
}
int fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}
int fibonacci_iterative(int n) {
    int stack[100];  
    int top = -1;
    stack[++top] = n;
    int result = 0;
    while (top >= 0) {
        n = stack[top--];
        if (n <= 1) {
            result += n;
        } else {
            stack[++top] = n - 1;
            stack[++top] = n - 2;
        }
    }
    return result;
}
void dfs_recursive(int graph[MAX_NODES][MAX_NODES], int node, int visited[MAX_NODES], int n) {
    if (visited[node]) return;
    visited[node] = 1;
    printf("%d ", node);
    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs_recursive(graph, i, visited, n);
        }
    }
}
void dfs_iterative(int graph[MAX_NODES][MAX_NODES], int start, int n) {
    int stack[MAX_NODES];
    int top = -1;
    int visited[MAX_NODES] = {0};
    int node;
    stack[++top] = start;
    while (top >= 0) {
        node = stack[top--];
        if (!visited[node]) {
            visited[node] = 1;
            printf("%d ", node);

            for (int i = n - 1; i >= 0; i--) { 
                if (graph[node][i] && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
}
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
void postorder_recursive(TreeNode* root) {
    if (root == NULL) return;
    postorder_recursive(root->left);
    postorder_recursive(root->right);
    printf("%d ", root->val);
}
void postorder_iterative(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* stack[100];
    int top = -1;
    TreeNode* lastVisited = NULL;
    TreeNode* curr = root;
    while (curr != NULL || top >= 0) {
        if (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        } else {
            TreeNode* peekNode = stack[top];
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                curr = peekNode->right;
            } else {
                printf("%d ", peekNode->val);
                lastVisited = stack[top--];
            }
        }
    }
}
int main() {
    int n_factorial = 5;
    printf("Factorial (Recursive) of %d is %d\n", n_factorial, factorial_recursive(n_factorial));
    printf("Factorial (Iterative) of %d is %d\n\n", n_factorial, factorial_iterative(n_factorial));
    int n_fibonacci = 6;
    printf("Fibonacci (Recursive) of %d is %d\n", n_fibonacci, fibonacci_recursive(n_fibonacci));
    printf("Fibonacci (Iterative) of %d is %d\n\n", n_fibonacci, fibonacci_iterative(n_fibonacci));
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}
    };
    int visited[MAX_NODES] = {0};
    printf("DFS (Recursive) starting from node 0: ");
    dfs_recursive(graph, 0, visited, 4);
    printf("\n");
    printf("DFS (Iterative) starting from node 0: ");
    dfs_iterative(graph, 0, 4);
    printf("\n\n");
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = 1;
    root->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->val = 2;
    root->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->right->val = 3;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right->left = NULL;
    root->right->right = NULL;
    printf("Postorder Traversal (Recursive): ");
    postorder_recursive(root);
    printf("\n");
    printf("Postorder Traversal (Iterative): ");
    postorder_iterative(root);
    printf("\n");
    free(root->left);
    free(root->right);
    free(root);
    return 0;
}