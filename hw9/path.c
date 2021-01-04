#include <stdio.h>
#include "backend.h"

/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/
int state[N], parent[N], queue[N];
int p[N];

int shortest_path(start, goal)
{
    struct node* p;
    int rear, front, current;
    int k, adj;
    rear = 0;
    front = -1;

    for (k = 0; k < N; k++)
    {
        parent[k] = 0;
        state[k] = 0;
    }

    state[start] = 1;

    queue[rear] = start;
    rear++;
    parent[start] = -1;

    while (rear - front - 1 > 0)
    {
        front = front + 1;
        current = queue[front];
        p = adj_list[current];
        while (p != NULL)
        {
            k = p->index;
            if (state[k] != 1)
            {
                state[k] = 1;
                queue[rear] = k;
                rear++;
                parent[k] = current;
                if (goal == k)
                    return 1;
            }
            p = p->next;
        }


    }
    return 0;

}

void find_path(char start[5], char goal[5])
{
    int i, j, k, l;

    i = search_index(start);
    j = search_index(goal);


    if (i < 0) {
        printf("Sorry. ");
        print_five_chars(start);
        printf(" is not in the dicitonary.");
    }
    else if (j < 0) {
        printf("Sorry. ");
        print_five_chars(goal);
        printf(" is not in the dicitonary.");
    }
    else {
        int result;
        result = shortest_path(i, j);

        if (result == 0)
        {
            printf("Sorry. There is no path from ");
            print_five_chars(start);
            printf(" to ");
            print_five_chars(goal);
            printf(".\n");
        }
        else {
            int v, s;
            int l;

            v = j;
            k = 0;
            while (v != i) {
                p[k] = v;
                k++;
                v = parent[v];

            }
            l = k;
            p[k] = i;
            while (k >= 0)
            {
                printf("          %d ", l - k);
                print_word(p[k]);
                printf("\n");
                k--;
            }
        }
    }
}


