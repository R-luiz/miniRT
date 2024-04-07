/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:27:36 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/29 11:10:38 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Function to create a sphere from parameters
t_sphere	*create_sphere(t_arena *arena, char **params)
{
	char		*delimiter;
	t_sphere	*sphere;

	delimiter = ",";
	sphere = (t_sphere *)arena_alloc(arena, sizeof(t_sphere));
	sphere->center = (t_point3){
		safe_atof(arena, ft_strtok(params[0], delimiter)),
		safe_atof(arena, ft_strtok(NULL, delimiter)),
		safe_atof(arena, ft_strtok(NULL, delimiter))
	};
	sphere->diameter = safe_atof(arena, params[1]);
	sphere->color = color_int(
			safe_atoi(arena, ft_strtok(params[2], delimiter)),
			safe_atoi(arena, ft_strtok(NULL, delimiter)),
			safe_atoi(arena, ft_strtok(NULL, delimiter))
			);
	sphere->bounce = NULL;
	sphere->hit_dist = &hit_sphere_distance;
	sphere->type = 1;
	return (sphere);
}

t_list	*get_sphere_params(t_arena *arena, t_list *tmp, t_list *spheres)
{
	t_sphere	*sphere;
	char		*params[3];

	if (!tmp->data || !((t_list *)tmp->data)->next)
		free_and_exit_error(arena, "Invalid sphere parameters");
	tmp = ((t_list *)tmp->data)->next;
	params[0] = (char *)tmp->data;
	if (!is_coordinates(params[0]))
		free_and_exit_error(arena, "Invalid sphere coordinates");
	tmp = tmp->next;
	params[1] = str_is_float(arena, (char *)tmp->data,
			"Invalid sphere diameter");
	if (!float_in_range(safe_atof(arena, params[1]), 0, __FLT_MAX__))
		free_and_exit_error(arena, "Invalid sphere diameter");
	tmp = tmp->next;
	params[2] = (char *)tmp->data;
	if (!is_rgb(params[2]))
		free_and_exit_error(arena, "Invalid sphere color");
	sphere = create_sphere(arena, params);
	if (!spheres)
		spheres = ft_lstnew(arena, sphere);
	else
		ft_lstadd_back(&spheres, ft_lstnew(arena, sphere));
	return (spheres);
}

t_list	*find_spheres(t_arena *arena, t_list *list_params)
{
	t_list		*tmp;
	t_list		*spheres;
	char		*str;

	tmp = list_params->next;
	spheres = NULL;
	while (tmp)
	{
		str = (char *)((t_list *) tmp->data)->data;
		if (ft_strcmp(str, "sp") == 0)
			spheres = get_sphere_params(arena, tmp, spheres);
		tmp = tmp->next;
	}
	return (spheres);
}
