#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-bst.h"     

#define POOL_SIZE 10

// record structure
struct record {
    char name[3];
    char number[4];
    struct record* left;
    struct record* right;
};

void print_name(struct record*);
void print_number(struct record*);

// pool of memory
static struct record pool[POOL_SIZE]; // static because pool is strictly private
struct record* top = pool;  // a pointer variable for pool stack top.

// comparison function for records
int compare(char key[3], struct record*);

// data
struct record* data = NULL; // Initially NULL.


void init_pool() // Initialize the pool; Use right instead of next!!!
{
    int i;
    struct record* r = pool;
    struct record* s;

    pool[POOL_SIZE - 1].right = NULL;

    for (i = 1; i < POOL_SIZE; i++) {
        s = r++;
        s->right = r;
    }
}

// Get a node from the pool. Returns NULL if pool is empty. 
// When calling new_node(), make sure to check if it is NULL. 
struct record* new_node()
{
    struct record* r;

    if (top == NULL)
        return NULL;

    r = top;
    top = r->right;  // Again, right instead of next.
    return r;
}

// Push a node to the pool.
void free_node(struct record* r)
{
    r->right = top;  // Again, right instead of next.
    top = r;
}


/***********************
Address Book by binary search tree
**************************/

void search(char name[3])
{
    struct record* r; // Pointer to record being compared.
                      //data or left/right field of a node.
    int result;
    r = data;

    while (r != NULL) {
        if ((result = compare(name, r)) < 0)
            r = r->left;
        else if (result == 0) {
            print_name(r);
            printf(" : ");
            print_number(r);
            printf(" was found.\n");
            return;
        }
        else // case >0
            r = r->right;
    }
    printf("Couldn't find the name.\n");
}


void add(char* name, char* number)
{
    struct record* r = NULL;
    struct record* p = data;
    struct record* q;
    int result;
    while (p != NULL)
    {
        if (compare(name, p) <= 0)
        {
            r = p;
            p = p->left;
        }
        else
        {
            r = p;
            p = p->right;
        }
    }

    q = new_node();

    if (q == NULL)
    {
        printf("Can't add.  The pool is empty!\n");

    }
    else
    {
        strcpy(q->name, name);
        strcpy(q->number, number);
        q->left = NULL;
        q->right = NULL;
    }

    if (data == NULL)
    {
        data = q;

    }
    else if (compare(name, r) <= 0)
    {
        r->left = q;

    }
    else
    {
        r->right = q;

    }
    printf("The name was successfully added!\n");


    // Messages to print
    //  printf("Can't add.  The pool is empty!\n");
    //  printf("The name was successfully added!\n");
}


// The most complicated.
void delete(char name[3])
{
    // Messages to print
//  printf("The name was deleted.\n");  
//  printf("Couldn't find the name.\n");
    struct record* r = data;
    struct record* p;

    while (r != NULL)
    {
        if (compare(name, r) < 0)
        {
            p = r;
            r = r->left;
        }
        else if (compare(name, r) == 0)
        {
            break;
        }
        else if (compare(name, r) > 0)
        {
            p = r;
            r = r->right;
        }
    }
    if (r == NULL)
    {
        printf("Couldn't find the name.\n");
        return;
    }

    if ((r->left == NULL) && (r->right == NULL))
    {
        if (p->left == r)
        {
            p->left = NULL;
        }
        else if (p->right == r)
        {
            p->right = NULL;
        }


    }
    else if ((r->left == NULL) || (r->right == NULL))
    {
        if ((p->left == r) && (p->right != r))
        {
            if ((r->left == NULL) && (r->right != NULL))
            {
                p->left = r->right;
                r = NULL;
            }
            else if ((r->left != NULL) && (r->right == NULL))
            {
                p->left = r->left;
                r = NULL;
            }
        }
        else if ((p->left != r) && (p->right == r))
        {
            if ((r->left == NULL) && (r->right != NULL))
            {
                p->right = r->right;
                r = NULL;
            }
            else if ((r->left != NULL) && (r->right == NULL))
            {
                p->right = r->left;
                r = NULL;
            }
        }
    }
    else if ((r->left != NULL) && (r->right != NULL))
    {
        struct record* succ, * succ_p;
        succ_p = r;
        succ = r->right;
        while (succ->left != NULL)
        {
            succ_p = succ;
            succ = succ->left;
        }
        strcpy(r->name, succ->name);
        strcpy(r->number, succ->number);
        succ_p->left = succ->right;

    }
    printf("The name was deleted.\n");
}


/* Just a wrapper of strncmp().
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
????if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record* r)
{
    return strncmp(key, r->name, 3);
}


void print_data(char* s, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(s[i]);
}

void print_name(struct record* r)
{
    print_data(r->name, 3);
}

void print_number(struct record* r)
{
    print_data(r->number, 4);
}

void print_inorder(struct record* t)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        print_inorder(t->left);
        print_name(t);
        printf(" : ");
        print_number(t);
        printf("\n");
        print_inorder(t->right);
    }
}

void print_list()
{
    print_inorder(data);
}


// returns the height of the BST.
int height(struct record* t)
{
    int a = 0;

    if (t == NULL)
    {
        return -1;
    }
    else if (t != NULL)
    {
        if (height(t->left) > height(t->right))
        {
            a = 1 + height(t->left);
        }
        else {
            a = 1 + height(t->right);
        }

        return a;

    }

    // dummy return.  Should return a valid height.
}

void print_height()
{
    printf("The Address Book BST's height is %d.\n", height(data));
}

