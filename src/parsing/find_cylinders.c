/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cylinders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:49:50 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/26 11:34:59 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cylinder	*parse_cylinder_params(t_arena *arena, t_list *params)
{
	t_cylinder	*cylinder;
	char		*str;
	char		*delimiter;

	cylinder = (t_cylinder *)arena_alloc(arena, sizeof(t_cylinder));
	str = (char *)params->data;
	delimiter = ",";
	cylinder->center = (t_point3){ft_atof(ft_strtok(str, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))};
	str = (char *)params->next->data;
	cylinder->normal = (t_vec3){ft_atof(ft_strtok(str, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))};
	str = (char *)params->next->next->data;
	cylinder->diameter = ft_atof(str);
	str = (char *)params->next->next->next->data;
	cylinder->height = ft_atof(str);
	str = (char *)params->next->next->next->next->data;
	cylinder->color = color_vec3((t_vec3){ft_atof(ft_strtok(str, delimiter)),
			ft_atof(ft_strtok(NULL, delimiter)),
			ft_atof(ft_strtok(NULL, delimiter))});
	return (cylinder);
}

t_list	*find_cylinders(t_arena *arena, t_list *list_params)
{
	t_list		*tmp;
	t_list		*cylinders;
	t_cylinder	*cylinder;

	tmp = list_params->next;
	cylinders = NULL;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->data, "cy") == 0)
		{
			cylinder = parse_cylinder_params(arena, (t_list *)tmp->next->data);
			if (!cylinders)
				cylinders = ft_lstnew(arena, cylinder);
			else
				ft_lstadd_back(&cylinders, ft_lstnew(arena, cylinder));
		}
		tmp = tmp->next;
	}
	return (cylinders);
}
