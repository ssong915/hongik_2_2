#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define SUCCESS_MESSAGE "All the words were successfully read!\n"
#define WELCOME_MESSAGE "Welcome to Search!\n"
#define SEARCH_PROMPT ">"
#define POOL_SIZE 5757

void get_words();
int binary_search(char name[5]);
int prompt_name(char* , char* );

char word[5757][5];

int main()
{
    char buff[100];

    get_words();

    printf(SUCCESS_MESSAGE);
    printf(WELCOME_MESSAGE);

    while (1)
    {
    restart:

        if (prompt_name(SEARCH_PROMPT, buff) != 0)
            goto restart;
        binary_search(buff);

    }    

}

void get_words()
{
    FILE* fp = NULL;
    fp = fopen("words.dat", "r");

    char buff[100];
    char arr[5];
    int i ;
    int j ;

    for (i = 0; i < 4; i++)
    {
        fgets(buff, 100, fp);
    }

    for (i = 0; i < 5757; i++)
    {
        fgets(buff, 100, fp);
        for (j = 0; j < 5; j++)
        {
            word[i][j] = buff[j];
        }
    }

}

int binary_search(char name[5])
{
    int l = 0;
    int u = 5756;

    int m,result;

    while (1)
    {
    step1:
        {
            m = (l + u) / 2;
            goto step2;
        }
    step2:
        {
            result = strncmp(word[m], name, 5);

            if (result >0)
            {
                u = m - 1;
                goto step3;
            }
            else if (result<0)
            {
                l = m + 1;
                goto step3;
            }
            else if (result == 0)
            {
                printf("%d\n", m);
                break;
            }
        }
    step3:
        {
            if (u < l)
            {
                printf("%d\n", -1);
                break;
            }
            else
            {
                goto step1;
            }
        }
    }
        
 
}

int prompt_name(char* s, char* p)
{
    char* q;
    char c;

    while (1) {
        printf("%s ", s);
        fflush(stdout);
        q = p;
        while (1) {
            c = getchar();
            if (c == EOF)
                exit(0);      // Should let exit() take care of the sudden EOF.
            if (c == '\n')
                break;
            if (q < p + 5)
                *q = c;
            q++;
        }
        if (q == p + 5)
            return 0;   // got a good name //

        printf("(Please type five lowercase letters and RETURN.)\n");
    }
}
