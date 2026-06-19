#include <stdio.h>
#define MAX 100

void Delete(char *list, int len, char l, char r, int *newLen)
{
    int i = 0,k = 0;
    for (i = 0; i < len; i++)
    {
        if (list[i] < l || list[i] > r)
        {
            list[k++] = list[i];
        }
    }
    *newLen = k;
}

void Show(char *list, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        printf("%c ", list[i]);
    }
    printf("\n");
}

int main()
{
    char List[] = {'1','2','3','1','1','0','4','2','3','1','0','4','2'};
    int len = int(sizeof(List) / sizeof(List[0]));
    int newLen = 0;
    Show(List, len);
    Delete(List, len, '2', '3', &newLen);
    printf("\n");
    Show(List, newLen);

    return 0;
}