#include "get_next_line.h"

l_list *find_last(l_list *list)
{
    if (list == NULL)
        return (NULL);
    while (list->next != NULL)
        list = list->next;
    return (list);
}

// create_list function
int search_for_newline(l_list *list)
{
    int i;

    if (list == NULL)
        return (0);
    while (list)
    {
        i = 0;
        while (list->current[i] && i < BUFF_SIZE )
        {
            if (list->current[i] == '\n')
                return (1);
            i++;
        }
        list = list->next;
    }
    return (0);
}

void add_buf(l_list **list, char *buf)
{
    l_list *new; 
    l_list *last; 

    last = find_last(*list);
    new = (l_list *)malloc(sizeof(l_list));
    if (new == NULL)
        return ;
    if (last == NULL)
        *list = new;
    else 
        last->next = new;
    new->current = buf;
    new->next = NULL;
}


// get_line function 
int len_newline(l_list *list)
{
    int i;
    int len;

    len = 0;
    if (list == NULL)
        return (len);
   while (list)
   {
        i = 0;
        while (list->current[i])
        {
            if (list->current[i] == '\n')
            {
                len++;
                return (len);
            }
            i++;
            len++;
        }
        list = list->next;
   }
   return (len);
}

void strcopy(l_list *list, char *str)
{
    int i;
    int k;

    if (list == NULL)
        return ;
    k = 0;
    while (list)
    {
        i = 0;
        while (list->current[i])
        {
            if (list->current[i] == '\n')
            {
                str[k++] = '\n';
                str[k] = '\0';
                return ;
            }
            str[k++] = list->current[i++];
        }
        list = list->next;
    }
    str[k] = '\0';
}

//free_list function 
void free_all(l_list **list, l_list *clean, char *buf)
{
    l_list *tmp;

    if (*list == NULL)
        return ;
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->current);
        free(*list);
        *list = tmp;
    }
    *list = NULL;
    if (clean->current[0])
        *list = clean;
    else
    {
        free(buf);
        free(clean);
    }
}