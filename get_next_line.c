/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:56:57 by opopov            #+#    #+#             */
/*   Updated: 2025/01/04 18:54:57 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

void	add_buf(t_list **list, char *buf)
{
	t_list	*new;
	t_list	*last;

	last = find_last(*list);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	if (last == NULL)
		*list = new;
	else
		last->next = new;
	new->current = buf;
	new->next = NULL;
}

void	free_list(t_list **list)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		k;
	char	*buf;

	buf = (char *)malloc(BUFF_SIZE + 1);
	clean = (t_list *)malloc(sizeof(t_list));
	if (buf == NULL || clean == NULL)
		return ;
	last = find_last(*list);
	i = 0;
	k = 0;
	while (last->current[i] && last->current[i] != '\n')
		i++;
	while (last->current[i] && last->current[++i])
		buf[k++] = last->current[i];
	buf[k] = '\0';
	clean->current = buf;
	clean->next = NULL;
	free_all(list, clean, buf);
}

char	*get_line(t_list *list)
{
	int		len;
	char	*next;

	if (list == NULL)
		return (NULL);
	len = len_newline(list);
	next = (char *)malloc(len + 1);
	if (next == NULL)
		return (NULL);
	strcopy(list, next);
	return (next);
}

void	create_list(t_list **list, int fd)
{
	char	*buf;
	int		readable;

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

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, &next, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next = get_line(list);
	free_list(&list);
	return (next);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *a;
// 	while ((a = get_next_line(fd)))
// 		printf("%s", a);
// 	return (0);
// }
