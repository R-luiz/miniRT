/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:42:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/28 17:33:24 by rluiz            ###   ########.fr       */
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

t_object *convert_sph_to_obj(t_arena *arena, t_sphere *sphere)
{
	t_object *object;

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

t_object *convert_pln_to_obj(t_arena *arena, t_plane *plane)
{
	t_object *object;

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

t_object *convert_cyl_to_obj(t_arena *arena, t_cylinder *cylinder)
{
	t_object *object;

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

t_list	*list_all(t_list *spheres, t_list *planes, t_list *cylinders, t_arena *arena)
{
	t_list	*all;
	t_object	*object;

	all = NULL;
	while (spheres)
	{
		object = convert_sph_to_obj(arena, (t_sphere *)spheres->data);
		if (!all)
			all = ft_lstnew(arena, object);
		else
			ft_lstadd_back(&all, ft_lstnew(arena, object));
		spheres = spheres->next;
	}
	while (cylinders)
	{
		ft_lstadd_back(&all, ft_lstnew(arena, convert_cyl_to_obj(arena, (t_cylinder *)cylinders->data)));
		cylinders = cylinders->next;
	}
	while (planes)
	{
		ft_lstadd_back(&all, ft_lstnew(arena, convert_pln_to_obj(arena, (t_plane *)planes->data)));
		planes = planes->next;
	}
	return (all);
}

t_objects	*init_objects(t_arena *arena, char *argv[])
{
	t_objects	*objects;
	t_list		*params;

	params = parsing_to_list(arena, argv[1]);
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
	objects->ob_count = objects->sp_count + objects->pl_count + objects->cy_count;
	objects->all = list_all(objects->spheres, objects->planes, objects->cylinders, arena);
	return (objects);
}
