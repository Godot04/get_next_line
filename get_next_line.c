#include "get_next_line.h"

static void free_list(l_list **list)
{
    l_list *last;
    l_list *clean;
    int i;
    int k;
    char *buf;

    buf = (char *)malloc(BUFF_SIZE + 1);
    clean = (l_list *)malloc(sizeof(l_list));
    if (buf == NULL || clean == NULL)
        return ;
    last = find_last(*list);
    i = 0;
    k = 0;
    while (last->current[i] != '\n' && last->current[i] != '\0')
        i++;
   while (last->current[i] != '\n' && last->current[++i] != '\0')
        buf[k++] = last->current[i]; 
    buf[k] = '\0';
    clean->current = buf;
    clean->next = NULL;
    free_all(list, clean, buf);
}

static char *get_line(l_list *list)
{
    int len;
    char *next;
    if (list == NULL)
        return (NULL);
    len = len_newline(list);
    next = (char *)malloc(len + 1); 
    if (next == NULL)
        return (NULL);
    strcopy(list, next);
    return (next);
}

static void create_list(l_list **list, int fd)
{
    char *buf; 
    int readable;
    while (search_for_newline(*list) != 1)
    {
        buf = (char *)malloc(BUFF_SIZE + 1);
        if (buf == NULL)
            return ;
        readable = read(fd, buf, BUFF_SIZE);
        if (readable == 0)
        {
            free(buf);
            return ;
        }
        buf[readable] = '\0';
        add_buf(list, buf);
    }
}

char *get_next_line(int fd)
{
    static l_list *list = NULL;
    char *next; 
    if (fd < 0 || BUFF_SIZE <= 0)
        return (NULL);
    create_list(&list, fd);
    if (list == NULL)
        return (NULL);
    next = get_line(list);
    free_list(&list);
    return (next);
}

#include <stdio.h>
int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *a;
    while ((a = get_next_line(fd)))
        printf("%s", a);
    return (0);
}