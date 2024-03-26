/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:27:36 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/26 15:33:49 by rluiz            ###   ########.fr       */
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
		ft_atof(ft_strtok(params[0], delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))
	};
	sphere->diameter = ft_atof(params[1]);
	sphere->color = color_int(
			ft_atoi(ft_strtok(params[2], delimiter)),
			ft_atoi(ft_strtok(NULL, delimiter)),
			ft_atoi(ft_strtok(NULL, delimiter))
			);
	sphere->bounce = NULL;
	sphere->hit_dist = &hit_sphere_distance;
	return (sphere);
}

t_list	*find_spheres(t_arena *arena, t_list *list_params)
{
	t_list		*tmp;
	t_list		*spheres;
	char		*str;
	char		*params[3];
	t_sphere	*sphere;

	tmp = list_params->next;
	spheres = NULL;
	while (tmp)
	{
		str = (char *)((t_list *) tmp->data)->data;
		if (ft_strcmp(str, "sp") == 0)
		{
			params[0] = (char *)((t_list *) tmp->data)->next->data;
			params[1] = (char *)((t_list *) tmp->data)->next->next->data;
			params[2] = (char *)((t_list *) tmp->data)->next->next->next->data;
			sphere = create_sphere(arena, params);
			if (!spheres)
				spheres = ft_lstnew(arena, sphere);
			else
				ft_lstadd_back(&spheres, ft_lstnew(arena, sphere));
		}
		tmp = tmp->next;
	}
	return (spheres);
}
