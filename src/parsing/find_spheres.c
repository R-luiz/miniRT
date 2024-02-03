/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:27:36 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/03 15:48:51 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list  *find_spheres(t_arena *arena, t_list *list_params)
{
	t_list  *tmp;
	t_list  *tmp2;
	t_sphere  *sphere;
	t_list  *spheres;
	char    *str;
	char    *delimiter;

	tmp = list_params->next;
	spheres = NULL;
	while (tmp)
	{
		tmp2 = tmp->data;
		str = (char *)tmp2->data;
		if (ft_strcmp(str, "sp") == 0)
		{
			
			sphere = (t_sphere *)arena_alloc(arena, sizeof(t_sphere));
			tmp2 = tmp2->next;
			str = (char *)tmp2->data;
			delimiter = ",";
			sphere->center = (t_point3){ft_atof(ft_strtok(str, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter))};
			str = (char *)tmp2->next->data;
			sphere->diameter = ft_atof(str);
			str = (char *)tmp2->next->next->data;
			sphere->color = color_int(ft_atoi(ft_strtok(str, delimiter)),
				ft_atoi(ft_strtok(NULL, delimiter)),
				ft_atoi(ft_strtok(NULL, delimiter)));
			if (!spheres)
				spheres = ft_lstnew(arena, sphere);
			else
				ft_lstadd_back(&spheres, ft_lstnew(arena, sphere));
		}
		tmp = tmp->next;
	}
	return (spheres);
}
