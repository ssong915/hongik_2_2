#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "memory.h"

void print_name(struct record*);
void print_number(struct record*);
void print_data(char*, int);


// comparison function for records
int compare(char key[3], struct record*);

// data
struct record* data = NULL; // Initially NULL.


void init()
{
    init_pool();
}

void add(char* name, char* number)
{
    struct record* p=data;
    struct record* pnew=new_node();
    struct record* k=NULL;  

    if (pnew== NULL)
    {
        printf("Can't add.  The address book is full!\n");
    }
    else
    {
        strcpy(pnew->name, name);
        strcpy(pnew->number, number);


        if( p!=NULL)
        {
            while (p != NULL) 
            {
                if (compare(pnew->name,p) > 0)
                {
                    k =p;
                    p = p->next;                    
                }
                else
                {
                    break;
                }
              
            }

            if (k == NULL)
            {
                pnew->next = p;
                data = pnew;
            }
            else if(k !=NULL)
            {
                pnew->next = p;
                k->next = pnew;
            }
        }
        else if (data == NULL)
        {
            pnew->next = p;
            data = pnew;
            p = data;
        }

    }

}




void search(char name[3])
{
    struct record* r = data;
    int result;

    while (r != NULL && (result = compare(name, r)) != 0)
        r = r->next;
    if (r == NULL)
        printf("Couldn't find the name.\n");
    else {
        print_name(r);
        printf(" : ");
        print_number(r);
        printf(" was found.\n");
    }
}


void delete(char name[3])
{
    struct record* r = data;
    struct record* q = NULL;
    int result;
    while (r != NULL && (compare(name, r)) != 0)
    {
        q = r;
        r = r->next;
    }

    if ((compare(name, r)) == 0)
    {
        if (r==data)
        {
            data = r->next;
            free_node(r);
            printf("The name was deleted.\n");
        }
        else
        {
            q->next = r->next;
            free_node(r);
            printf("The name was deleted.\n");
        }
    }
    else
    {
        printf("Couldn't find the name.\n");

    }
    // Error Message:
    // printf("Couldn't find the name.\n");
}


/* Just a wrapper of strncmp(), except for the case r is NULL.
Regard strncmp(a,b) as a-b, that is,
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record* r)
{
    if (r == NULL)
        return -1;
    else
        return strncmp(key, r->name, 3);
}

// Prints ith name.
void print_name(struct record* r)
{
    print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record* r)
{
    print_data(r->number, 4);
}

void print_data(char* s, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(s[i]);
}

void print_list()
{
    struct record* p;
    p = data;
    while (p != NULL)
    {
        print_name(p);
        printf(" : ");
        print_number(p);
        printf("\n");
        p = p->next;
    }
}

