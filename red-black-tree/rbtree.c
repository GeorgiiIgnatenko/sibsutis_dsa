#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

node* null = NULL;


void init_null()
{
    if (null)
        return;
    null = (node*)malloc(sizeof(*null));
    null->parent = NULL;
    null->left = NULL;
    null->right = NULL;
    null->color = 0;
    null->key = -1;
}


node* createNode(int key, char* value) {
    node* newNode = malloc(sizeof(node));
    if (newNode == NULL)
        return NULL;

    newNode->key = key;
    newNode->value = value;
    newNode->parent = null;
    newNode->right = null;
    newNode->left = null;
    newNode->color = 1;

    printf("Created Node\n");
    printf("Key: %d\n", key);
    printf("Value: %s\n", value);
    printf("\n");
    return newNode;
}; 

void LeftRotate(struct rbtree* T, node* x) {
    node* y = x->right;
    x->right = y->left;

    if (y->left != null){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == null){
        T->root = y;
    }else if (x == x->parent->left){
        x->parent->left = y;
    }else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RightRotate(struct rbtree* T, node* x) {
    node* y = x->left;
    x->left = y->right;

    if (y->right != null) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == null){
        T->root = y;
    }else if (x == x->parent->left){
        x->parent->left = y;
    }else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

void rbtree_Add_Fixup(struct rbtree* T, node* z) {
    if (z == T->root){
        z->color = 0;
        return;
    }

    while (z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            node *y = z->parent->parent->right;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }else {
                if (z == z->parent->right){
                    z = z->parent;
                    LeftRotate(T, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                RightRotate(T, z->parent->parent);
            }
        }else{
            node *y = z->parent->parent->left;
            if (y->color == 1){
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }else {
                if (z == z->parent->left){
                    z = z->parent;
                    RightRotate(T, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                LeftRotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = 0;
}

struct rbtree *rbtree_add(struct rbtree* T, int key, char *value){
    node* z = createNode(key, value);
    node* x = T->root;
    node* y = null;
    while (x != null){
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == null)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = null;
    z->right = null;
    z->color = 1;
    rbtree_Add_Fixup(T, z);
    return T;
}

node *rbtree_lookup(struct rbtree *T, int key) {
    node* head = T->root;
    while (head != null){
        if (head->key == key) {
            printf("Element with key: %d found\n", key);
            printf("Element value: %s\n", head->value);
            printf("\n");
            return head;
        }else {
            if (head->key < key) {
                head = head->right;
            }else {
                head = head->left;
            }
        }
    }
    printf("Element with key: %d not found :(\n", key);
    printf("\n");
    return head;
}

void rbtree_transplant(struct rbtree *T, node* oldNode, node* newNode){
    if (oldNode->parent == null)
        T->root = newNode;
    else if (oldNode == oldNode->parent->left)
        oldNode->parent->left = newNode;
    else
        oldNode->parent->right = newNode;
    newNode->parent = oldNode->parent;
}

void rbtree_Delete_Fixup(struct rbtree *T, node *x){
    while (x != T->root && x->color == 0){
        if (x == x->parent->left){
            node *w = x->parent->right;
            if (w->color == 1){
                w->color = 0;
                x->parent->color = 1;
                LeftRotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0){
                w->color = 1;
                x = x->parent;
            }else{
                if (w->right->color == 0){
                    w->left->color = 0;
                    w->color = 1;
                    RightRotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                LeftRotate(T, x->parent);
                x = T->root;
            }
        }else{
            node *w = x->parent->left;
            if (w->color == 1){
                w->color = 0;
                x->parent->color = 1;
                RightRotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0){
                w->color = 1;
                x = x->parent;
            }else{
                if (w->left->color == 0){
                    w->right->color = 0;
                    w->color = 1;
                    LeftRotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                RightRotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = 0; 
}

struct rbtree *rbtree_delete(struct rbtree *T, int key) {
    node* z = rbtree_lookup(T, key);
    node* y = z;
    node* x = NULL;
    int yOriginalColor = y->color;

    if (z->left == null){
        x = z->right;
        rbtree_transplant(T, z, z->right);
    }else if (z->right == null){
        x = z->left;
        rbtree_transplant(T, z, z->left);
    }else {
        y = rbtree_min(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y != z->right){
            rbtree_transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }else {
            x->parent = y;
        }
        rbtree_transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == 0){
        rbtree_Delete_Fixup(T, x);
    }

    free(z);
    
    return T;
}

node *rbtree_min(node *head) {
    while (head->left != null) {
        head = head -> left;
    }
    printf("Min Key: %d\n", head->key); 
    printf("Node Value: %s\n", head->value);
    printf("\n");
    return head;
}

node *rbtree_max(node *head) {
    while (head->right != null) {
        head = head -> right;
    }
    printf("Max Key: %d\n", head->key);
    printf("Node Value: %s\n", head->value);
    printf("\n");
    return head;
}
void rbtree_free(node *root) {

    if (root->right != null)
        rbtree_free(root->right);
    if (root->left != null)
        rbtree_free(root->left);

    free(root);
    printf("freed\n");
}
void rbtree_print_dfs(node *root) {
    if (root->color == 1){
        printf("\e[38;5;1m[%d]\e[0m ", root->key);
    }
    else{
        printf("[%d] ", root->key);
    }
    if (root->left != null)
        rbtree_print_dfs(root->left);
    if (root->right != null)
        rbtree_print_dfs(root->right);

}


int main() {
    init_null();

    struct rbtree tree;
    tree.root = null;
    rbtree_add(&tree, 1, "TEST");
    rbtree_add(&tree, 10, "Test2");
    rbtree_add(&tree, 15, "Fulman eblan :D");
    rbtree_add(&tree, 3, "Test2");
    rbtree_add(&tree, 5, "Test2");
    rbtree_lookup(&tree, 15);
    rbtree_lookup(&tree, 20);
    rbtree_lookup(&tree, 1);
    rbtree_lookup(&tree, 10);
    rbtree_lookup(&tree, 3);
    rbtree_min(tree.root);
    rbtree_max(tree.root);

    rbtree_print_dfs(tree.root);
    printf("\n");

    rbtree_delete(&tree, 10);

    rbtree_free(tree.root);
    free(null);
    null = NULL;
}
