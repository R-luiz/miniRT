/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:42:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/01 15:19:21 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*token_to_list(t_arena *arena, char *line)
{
	char	*token;
	char	*delimiter;
	t_list	*list;
	t_list	*tmp;

	delimiter = " ";
	list = (t_list *)arena_alloc(arena, sizeof(t_list));
	tmp = list;
	token = ft_strtok(line, delimiter);
	tmp->data = ft_strdup(token);
	while (token)
	{
		token = ft_strtok(NULL, delimiter);
		tmp->next = ft_lstnew(arena, ft_strdup(token));
		tmp = tmp->next;
	}
	return (list);
}

t_list	*parsing_to_list(t_arena *arena, char *file)
{
	int		fd;
	char	*line;
	t_list	*list;
	t_list	*tmp;

	list = (t_list *)arena_alloc(arena, sizeof(t_list));
	tmp = list;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		tmp->next =	token_to_list(arena, line);
		tmp = tmp->next;
	}
	close(fd);
	return (list);
}
