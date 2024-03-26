/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_planes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:44:55 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/26 11:28:57 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_plane	*parse_plane_params(t_arena *arena, t_list *params)
{
	t_plane	*plane;
	char	*str;
	char	*delimiter;

	plane = (t_plane *)arena_alloc(arena, sizeof(t_plane));
	str = (char *)params->data;
	delimiter = ",";
	plane->apoint = (t_point3){ft_atof(ft_strtok(str, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))};
	str = (char *)params->next->data;
	plane->normal = (t_vec3){ft_atof(ft_strtok(str, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter)),
		ft_atof(ft_strtok(NULL, delimiter))};
	str = (char *)params->next->next->data;
	plane->color = color_int(ft_atoi(ft_strtok(str, delimiter)),
			ft_atoi(ft_strtok(NULL, delimiter)),
			ft_atoi(ft_strtok(NULL, delimiter)));
	return (plane);
}

t_list	*find_planes(t_arena *arena, t_list *list_params)
{
	t_list	*tmp;
	t_list	*planes;
	t_plane	*plane;

	tmp = list_params->next;
	planes = NULL;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->data, "pl") == 0)
		{
			plane = parse_plane_params(arena, (t_list *)tmp->next->data);
			if (!planes)
				planes = ft_lstnew(arena, plane);
			else
				ft_lstadd_back(&planes, ft_lstnew(arena, plane));
		}
		tmp = tmp->next;
	}
	return (planes);
}
