#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *left, *right;
    int data;
};


// insert, delete, search, show


int insert_bst(int val, struct node **root)
{
    if (!(*root)) {
        struct node *n = calloc(1, sizeof(struct node));
        n->data = val;
        *root = n;
        return;
    }
    
    if ((*root)->data > val) {
        insert_bst(val, &((*root)->left));
    } else {
        insert_bst(val, &((*root)->right));
    }
}

struct node *search_bst(int val, struct node *root)
{
    if (!root) return NULL;

    if (root->data == val)
        return root;
    else if (root->data > val)
        search_bst(val, root->left);
    else
        search_bst(val, root->right);
}

void show_bst(struct node *root)
{
    if (!root) return;
    
    show_bst(root->left);
    printf("%d left=%d right=%d\n", root->data,
           root->left ? root->left->data : 0,
           root->right ? root->right->data: 0);
    show_bst(root->right);
}

/* OBSOLETE: replaced with merge_bst() */
struct node *_delete_bst(struct node *root)
{
    if (root->left == NULL && root->right == NULL)
        return NULL;
    else if (root->left != NULL && root->right != NULL) {
        struct node **new_root = &(root->left);
        while ((*new_root)->right)
            new_root = &(*new_root)->right;
        root->data = (*new_root)->data;
        *new_root = NULL;
        return root;
    } else {
        if (root->left != NULL)
            return root->left;
        else
            return root->right;
    }    
}

struct node *merge_bst(struct node *tl, struct node *tr)
{
    struct node *tmp;
    struct node *new_root;

    if (tl != NULL && tr != NULL) {
        if (tl->right == NULL) {
            printf("tl has no right\n");
            tl->right = tr;
            return tl;
        }
    
        tmp = tl;
        while (tmp->right->right != NULL)
            tmp = tmp->right;
        new_root = tmp->right;
        tmp->right = NULL;
        new_root->left = tl;
        new_root->right = tr;
        return new_root;
    } else {
        if (tl != NULL)
            return tl;
        else return tr;
    }
}

void test_merge(void)
{
    struct node *t1 = NULL, *t2 = NULL;
    struct node *n;

    insert_bst(20, &t1);
    insert_bst(10, &t1);
    insert_bst(30, &t1);
    show_bst(t1);

    insert_bst(60, &t2);
    insert_bst(50, &t2);
    insert_bst(70, &t2);
    show_bst(t2);

    n = merge_bst(t1, t2);
    show_bst(n);
}

int delete_bst(int val, struct node **root)
{
    if (!*root) return -1;
    if ((*root)->data == val) {
        printf("found=%p %d\n", *root, (*root)->data);
        /* *root = _delete_bst(*root); */
        *root = merge_bst((*root)->left, (*root)->right);
        return val;
    } else if ((*root)->data > val) {
        delete_bst(val, &(*root)->left);
    } else {
        delete_bst(val, &(*root)->right);
    }
}

#define MAX(a,b) ((a) > (b) ? (a) : (b))
int height_bst(struct node *root)
{
    if (!root)
        return 0;

    return MAX(height_bst(root->left), height_bst(root->right)) + 1;
}

int main(void)
{
    struct node *root = NULL;
    
    insert_bst(40, &root);
    insert_bst(20, &root);
    insert_bst(60, &root);
    insert_bst(10, &root);
    insert_bst(30, &root);
    insert_bst(50, &root);
    insert_bst(70, &root);
    insert_bst(25, &root);
    insert_bst(35, &root);
    insert_bst(65, &root);
    insert_bst(75, &root);
    show_bst(root);

    printf("%d\n", search_bst(65, root)->data);
    printf("%d\n", search_bst(25, root)->data);
    printf("%p\n", search_bst(22, root));

    insert_bst(45, &root);
    insert_bst(55, &root);
    show_bst(root);
    printf("%d\n", delete_bst(35, &root));
    show_bst(root);
    printf("%d\n", delete_bst(30, &root));
    show_bst(root);
    printf("%d\n", delete_bst(60, &root));
    show_bst(root);


    /* printf("---------------\n"); */
    /* test_merge(); */
    /* printf("-----------------\n"); */

    printf("%d\n", height_bst(root)); // =>4
    insert_bst(42, &root);
    printf("%d\n", height_bst(root)); // =>5

    
    return 0;
}
