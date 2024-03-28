/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_planes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:44:55 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/28 14:40:16 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_plane_params(char *str, t_list *tmp2, t_plane *plane)
{
	char	*delimiter;

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
	plane->bounce = NULL;
	plane->hit_dist = &hit_plane_distance;
	plane->type = 3;
}

t_plane	*create_plane(t_arena *arena, t_list *tmp2, char *str)
{
	t_plane	*plane;

	plane = (t_plane *)arena_alloc(arena, sizeof(t_plane));
	parse_plane_params(str, tmp2, plane);
	return (plane);
}

void	add_plane_to_list(t_arena *arena, t_list **planes, t_plane *plane)
{
	if (!(*planes))
		*planes = ft_lstnew(arena, plane);
	else
		ft_lstadd_back(planes, ft_lstnew(arena, plane));
}

t_list	*find_planes(t_arena *arena, t_list *list_params)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*planes;
	t_plane	*plane;
	char	*str;

	tmp = list_params->next;
	planes = NULL;
	while (tmp)
	{
		tmp2 = tmp->data;
		str = (char *)tmp2->data;
		if (ft_strcmp(str, "pl") == 0)
		{
			tmp2 = tmp2->next;
			str = (char *)tmp2->data;
			plane = create_plane(arena, tmp2, str);
			add_plane_to_list(arena, &planes, plane);
		}
		tmp = tmp->next;
	}
	return (planes);
}
