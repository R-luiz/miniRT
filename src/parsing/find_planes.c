/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_planes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:44:55 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/26 14:52:32 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*find_planes(t_arena *arena, t_list *list_params)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_plane	*plane;
	t_list	*planes;
	char	*str;
	char	*delimiter;

	tmp = list_params->next;
	planes = NULL;
	while (tmp)
	{
		tmp2 = tmp->data;
		str = (char *)tmp2->data;
		if (ft_strcmp(str, "pl") == 0)
		{
			plane = (t_plane *)arena_alloc(arena, sizeof(t_plane));
			tmp2 = tmp2->next;
			str = (char *)tmp2->data;
			delimiter = ",";
			plane->apoint = (t_point3){ft_atof(ft_strtok(str, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter))};
			str = (char *)tmp2->next->data;
			plane->normal = (t_vec3){ft_atof(ft_strtok(str, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter)),
				ft_atof(ft_strtok(NULL, delimiter))};
			str = (char *)tmp2->next->next->data;
			plane->color = color_int(ft_atoi(ft_strtok(str, delimiter)),
				ft_atoi(ft_strtok(NULL, delimiter)),
				ft_atoi(ft_strtok(NULL, delimiter)));
			if (!planes)
				planes = ft_lstnew(arena, plane);
			else
				ft_lstadd_back(&planes, ft_lstnew(arena, plane));
		}
		tmp = tmp->next;
	}
	return (planes);
}