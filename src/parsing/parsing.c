/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:42:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/27 15:02:05 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../camera/camera.h"

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
	tmp->data = ft_strdup(arena, token);
	while (token)
	{
		token = ft_strtok(NULL, delimiter);
		if (!token)
			break ;
		tmp->next = ft_lstnew(arena, ft_strdup(arena, token));
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
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(arena, fd);
	while (line)
	{
		tmp->next = ft_lstnew(arena, token_to_list(arena, line));
		tmp = tmp->next;
		line = get_next_line(arena, fd);
	}
	close(fd);
	return (list);
}

t_objects	*init_objects(t_arena *arena, char *argv[])
{
	t_objects	*objects;
	t_list		*params;

	params = parsing_to_list(arena, argv[1]);
	check_duplicated_capitals(arena, params);
	objects = arena_alloc(arena, sizeof(*objects));
	objects->camera = find_camera(arena, params, NULL);
	objects->ambient = find_ambient(arena, params, NULL);
	objects->light = find_light(arena, params, NULL);
	objects->spheres = find_spheres(arena, params);
	objects->planes = find_planes(arena, params);
	objects->cylinders = find_cylinders(arena, params);
	objects->sp_count = ft_lstsize(objects->spheres);
	objects->pl_count = ft_lstsize(objects->planes);
	objects->cy_count = ft_lstsize(objects->cylinders);
	return (objects);
}
