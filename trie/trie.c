#include "trie.h"

struct trie *trie_create(){
	struct trie *node;

	if ((node = malloc(sizeof(*node))) == NULL) 
		return NULL;

	node->ch = '\0';
	node->value = 0;
	node->sibling = NULL;
	node->child = NULL;

	return node;
}


struct trie *get_child(struct trie *node, char key) {
	struct trie *head = node;
	if (head->child != NULL){
		head = head->child;	
		if (head->ch == key)
			return head;	
		while (head->sibling != NULL){
			head = head->sibling;
			if (head->ch == key)
				return head;
		}
		return NULL;
	}else {
		return NULL;
	}	
}

struct trie *trie_insert(struct trie *root, char *key, char *value){
	struct trie *node, *parent, *list;

	parent = NULL;
	list = root;
	for (; *key != '\0'; key++) {
		for (node = list; node != NULL; node = node->sibling){
			if (node->ch == *key)
				break;
		}
		if (node == NULL) {
			node = trie_create();
			node->ch = *key;
			node->sibling = list;
			if (parent != NULL)
				parent->child = node;
			else
				root = node;
			list = NULL;
		} else
			list = node->child; 
		parent = node;
	}
	if (node->value != NULL)
		free(node->value);
	node->value = strdup(value);
	return root;
}

struct trie *trie_lookup(struct trie *root, char *key) {
	struct trie *node = root;
	for (int i = 0; key[i] != '\0'; i++){
		struct trie *child = get_child(node, key[i]);
		if (child == NULL)
			return NULL;
		node = child;
	}
	if (node->value == 0)
		return NULL;
	return node;
};

struct trie *trie_delete_dfs(struct trie *root, struct trie *parent,
			     char *key, int *found)
{
	struct trie *node, *prev = NULL;
	*found = (*key == '\0' && root == NULL) ? 1 : 0;
	if (root == NULL || *key == '\0')
		return root;

	for (node = root; node != NULL; node = node->sibling) {
		if (node->ch == *key)
			break;
		prev = node;
	}
	if (node == NULL)
		return root;
	trie_delete_dfs(node->child, node, key + 1, found);
	if (*found > 0 && node->child == NULL) {
		if (prev != NULL)
			prev->sibling = node->sibling;
		else{
			if (parent != NULL)
				parent->child = node->sibling;
			else
				root = node->sibling;
		}
		free(node->value);
		free(node);
	}
	return root;
}

struct trie *trie_delete(struct trie *root, char *key) {
	int found;
	return trie_delete_dfs(root, NULL, key, &found);
};

void print_spaces(int count)
{
	for (int i = 0; i < count; i++){
		printf("  ");
	}
}


void trie_print(struct trie *root, int level) {
	if (root == NULL)
		return;

	print_spaces(level);
	if (root->value != NULL) {
		printf("%c -> %s\n", root->ch, root->value);
	} else {
		printf("%c\n", root->ch);
	}

	trie_print(root->child, level+1);
	trie_print(root->sibling, level);
};

void trie_display(struct trie* root)
{
	trie_print(root, 0);
}


int main() {
	struct trie *root = trie_create();
	
	root = trie_insert(root, "test", "a");
	root = trie_insert(root, "temp", "b");
	root = trie_insert(root, "rat", "c");
	root = trie_insert(root, "red", "d");
	trie_display(root);
	root = trie_delete(root, "test");
	trie_display(root);

	return 0;
};
