/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cylinders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:49:50 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/02 17:50:35 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*find_cylinders(t_arena *arena, t_list *list_params)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_cylinder	*cylinder;
	t_list		*cylinders;
	char		*str;
	char		*delimiter;

	tmp = list_params->next;
	cylinders = NULL;
	while (tmp)
	{
		tmp2 = tmp->data;
		str = (char *)tmp2->data;
		if (ft_strcmp(str, "cy") == 0)
		{
			cylinder = (t_cylinder *)arena_alloc(arena, sizeof(t_cylinder));
			tmp2 = tmp2->next;
			str = (char *)tmp2->data;
			delimiter = ",";
			cylinder->center = (t_point3){ft_atof(ft_strtok(str, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter))};
			str = (char *)tmp2->next->data;
			cylinder->normal = (t_vec3){ft_atof(ft_strtok(str, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter))};
			str = (char *)tmp2->next->next->data;
			cylinder->diameter = ft_atof(str);
			str = (char *)tmp2->next->next->next->data;
			cylinder->height = ft_atof(str);
			str = (char *)tmp2->next->next->next->next->data;
			cylinder->color = color_vec3((t_vec3){ft_atof(ft_strtok(str, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter))});
			if (!cylinders)
				cylinders = ft_lstnew(arena, cylinder);
			else
				ft_lstadd_back(&cylinders, ft_lstnew(arena, cylinder));
		}
		tmp = tmp->next;
	}
	return (cylinders);
}
