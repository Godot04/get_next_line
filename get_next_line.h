#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFF_SIZE 
#define BUFF_SIZE 10
#endif

#include <stdlib.h>
#include <fcntl.h>
// #include <unistd.h>

typedef struct s_list
{
    char *current; //str buf
    struct s_list *next;
} l_list;

l_list *find_last(l_list *list);
int search_for_newline(l_list *list);
void add_buf(l_list **list, char *buf);
int len_newline(l_list *list);
void strcopy(l_list *list, char *str);
void free_all(l_list **list, l_list *clean, char *buf);

#endif