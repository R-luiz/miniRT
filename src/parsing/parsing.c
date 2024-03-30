/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:42:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/30 14:36:33 by vmalassi         ###   ########.fr       */
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
		free_and_exit_error(arena, "Error: file not found");
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

t_object	*convert_sph_to_obj(t_arena *arena, t_sphere *sphere)
{
	t_object	*object;

	object = (t_object *)arena_alloc(arena, sizeof(t_object));
	object->type = 1;
	object->hit_dist = sphere->hit_dist;
	object->bounce = NULL;
	object->center = sphere->center;
	object->normal = (t_vec3){0, 0, 0};
	object->diameter = sphere->diameter;
	object->height = 0;
	object->color = sphere->color;
	return (object);
}

t_object	*convert_pln_to_obj(t_arena *arena, t_plane *plane)
{
	t_object	*object;

	object = (t_object *)arena_alloc(arena, sizeof(t_object));
	object->type = 3;
	object->hit_dist = plane->hit_dist;
	object->bounce = NULL;
	object->center = plane->apoint;
	object->normal = plane->normal;
	object->diameter = 0;
	object->height = 0;
	object->color = plane->color;
	return (object);
}

t_object	*convert_cyl_to_obj(t_arena *arena, t_cylinder *cylinder)
{
	t_object	*object;

	object = (t_object *)arena_alloc(arena, sizeof(t_object));
	object->type = 2;
	object->hit_dist = cylinder->hit_dist;
	object->bounce = NULL;
	object->center = cylinder->center;
	object->normal = cylinder->normal;
	object->diameter = cylinder->diameter;
	object->height = cylinder->height;
	object->color = cylinder->color;
	return (object);
}
