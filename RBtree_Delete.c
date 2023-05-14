#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int key;
    char color;
    struct TreeNode* left, * right, * parent;
}TreeNode;

typedef struct
{
    TreeNode* root;
}TreeType;

TreeNode* Nil;

void init(TreeType* T)
{
    Nil = (TreeNode*)malloc(sizeof(TreeNode));
    Nil->color = 'B';
    T->root = Nil;
}

TreeNode* createNode(int key)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->left = node->right = node->parent = Nil;
    node->color = 'R';
    return node;
}


void leftRotate(TreeType* T, TreeNode* x)
{
    TreeNode* y = x->right;
    x->right = y->left;

    if (y->left != Nil)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == Nil)
        T->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(TreeType* T, TreeNode* x)
{
    TreeNode* y = x->left;
    x->left = y->right;

    if (y->right != Nil)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == Nil)
        T->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void insertFixup(TreeType* T, TreeNode* z)
{
    TreeNode* y;

    while (z->parent->color == 'R')
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y->color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(T, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(T, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if (y->color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(T, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(T, z->parent->parent);
            }
        }
    }

    T->root->color = 'B';
}

void insert(TreeType* T, int key)
{
    TreeNode* y = Nil;
    TreeNode* x = T->root;
    TreeNode* z = createNode(key);

    while (x != Nil)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == Nil)
    {
        T->root = z;
        T->root->color = 'B';
    }
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    insertFixup(T, z);
}

void preOrder(TreeNode* root)
{
    if (root != Nil)
    {
        printf("[%d(%c)] ", root->key, root->color);
        preOrder(root->left);
        preOrder(root->right);
    }
}

//key ���� ������ �ش� ��� ã�� �Լ�
TreeNode* findNode(TreeType* T, int key) 
{
    TreeNode* p = T->root;
    
    while (p != Nil) {
        if (key == p->key)
            return p;
        else if (key < p->key)
            p = p->left;
        else p = p->right;
    }
    return Nil;
}

void transplant(TreeType* T, TreeNode* u, TreeNode* v) {
    if (u->parent == Nil)
        T->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

TreeNode* minNode(TreeNode* root) {
    TreeNode* x = root;
    while (x->left != Nil) 
        x = x->left;
    return x;
}

void deleteFixup(TreeType* T, TreeNode* x) {
    TreeNode* w;
    while (x != T->root && x->color == 'B') 
    {
        if (x == x->parent->left) 
        {
            w = x->parent->right;
            if (w->color == 'R') 
            {
                w->color = 'B';
                x->parent->color = 'R';
                leftRotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B') 
            {
                w->color = 'R';
                x = x->parent;
            }
            else 
            {
                if (w->right->color == 'B') 
                {
                    w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                leftRotate(T, x->parent);
                x = T->root;
            }
        }

        else 
        {
            w = x->parent->left;
            if (w->color == 'R') 
            {
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 'B' && w->left->color == 'B') 
            {
                w->color = 'R';
                x = x->parent;
            }
            else 
            {
                if (w->left->color == 'B') 
                {
                    w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                rightRotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = 'B';
}

//Delete �Լ�
void delete(TreeType* T, int key) {
    TreeNode* x, * y, * z;

    z = findNode(T, key);     // z�� ������ ���

    y = z;
    char yOriginColor = y->color;   //������ ����� ��

    if (z->left == Nil) {
        //���� �ڽĳ�尡 ������
        x = z->right;
        transplant(T, z, z->right);
    }
    else if (z->right == Nil) {
        //������ �ڽĳ�尡 ������
        x = z->left;
        transplant(T, z, z->left);
    }
    else {
        //���� ��� �ڽĳ�尡 ������
        y = minNode(z->right);  //succesor
        yOriginColor = y->color;
        x = y->right;

        if (y->parent == z) 
            //x�� �θ� ������ ����� ���
            x->parent = y;
        else {
            transplant(T, y, y->right); //y�� z�ڸ��� �̵�
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(T, z, y);    //y�� z�ڸ��� �̽�
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;


    }

    //RB Ʈ���� Ư�� �Ѽս�
    if (yOriginColor == 'B') {
        deleteFixup(T, x);
    }

    return 0;
}

int main()
{
    TreeType T;
    init(&T);

    insert(&T, 8);
    insert(&T, 7);
    insert(&T, 12);
    insert(&T, 3);
    insert(&T, 6);
    insert(&T, 4);
    insert(&T, 5);
    insert(&T, 10); preOrder(T.root); printf("\n");

    //delete �׽�Ʈ
    delete(&T, 8); preOrder(T.root);


    return 0;
}
