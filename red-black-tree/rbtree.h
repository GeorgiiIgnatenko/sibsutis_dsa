typedef struct node{
    struct node* parent;
    struct node* left;
    struct node* right;
    int color;
    int key;
    char* value;
} node;

extern node* null;

struct rbtree{
    struct node* root;
};

struct rbtree *rbtree_add(struct rbtree *T, int key, char *value);
struct node *rbtree_lookup(struct rbtree *T, int key);
struct rbtree *rbtree_delete(struct rbtree *T, int key);
struct node *rbtree_min(node *head);
struct node *rbtree_max(node *head);
void rbtree_free(node *head);
void rbtree_print_dfs(node *root);
