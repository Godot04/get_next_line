/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:10:00 by opopov            #+#    #+#             */
/*   Updated: 2025/01/04 17:49:31 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE 10
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_list
{
	char			*current; //str buf
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*find_last(t_list *list);
int		search_for_newline(t_list *list);
void	add_buf(t_list **list, char *buf);
int		len_newline(t_list *list);
void	free_list(t_list **list);
void	strcopy(t_list *list, char *str);
void	create_list(t_list **list, int fd);
void	free_all(t_list **list, t_list *clean, char *buf);

#endif
