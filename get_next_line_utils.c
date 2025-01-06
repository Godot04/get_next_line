/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:57:20 by opopov            #+#    #+#             */
/*   Updated: 2025/01/06 21:30:22 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_list	*find_last(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

// create_list function
int	search_for_newline(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->current[i])
		{
			if (list->current[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

// get_line function
int	len_newline(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->current[i])
		{
			len++;
			if (list->current[i] == '\n')
				return (len);
			i++;
		}
		list = list->next;
	}
	return (len);
}

void	strcopy(t_list *list, char *str)
{
	int	i;
	int	k;

	if (list == NULL)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->current[i] && list->current[i] != '\n')
			str[k++] = list->current[i++];
		if (list->current[i] == '\n')
		{
			str[k++] = '\n';
			str[k] = '\0';
			return ;
		}
		list = list->next;
	}
	str[k] = '\0';
}

//free_list function
void	free_all(t_list **list, t_list *clean, char *buf)
{
	t_list	*tmp;

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
	if (clean && clean->current && clean->current[0])
		*list = clean;
	else
	{
		free(clean);
		free(buf);
	}
}
