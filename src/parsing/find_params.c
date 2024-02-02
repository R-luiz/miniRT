/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:47:05 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/02 17:39:34 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_camera	*find_camera(t_arena *arena, t_list *list)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_camera	*camera;
	char		*str;
	char		*delimiter;

	tmp = list->next;
	while (tmp)
	{
		tmp2 = tmp->data;
		tmp2 = tmp2->data;
		if (ft_strcmp(((t_list *)tmp->data)->data, "C") == 0)
		{
			tmp = tmp->data;
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	camera = (t_camera *)arena_alloc(arena, sizeof(t_camera));
	tmp = tmp->next;
	str = (char *)tmp->data;
	delimiter = ",";
	camera->center = (t_vec3){ft_atof(strtok(str, delimiter)),
		ft_atof(strtok(NULL, delimiter)), ft_atof(strtok(NULL, delimiter))};
	str = (char *)tmp->next->data;
	camera->look_at = (t_vec3){ft_atof(strtok(str, delimiter)),
		ft_atof(strtok(NULL, delimiter)), ft_atof(strtok(NULL, delimiter))};
	camera->hfov = ft_atof((char *)tmp->next->next->data);
	return (camera);
}

t_ambient	*find_ambient(t_arena *arena, t_list *list)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_vec3		vec;
	t_ambient	*ambient;
	char		*str;
	char		*delimiter;

	tmp = list->next;
	while (tmp)
	{
		tmp2 = tmp->data;
		tmp2 = tmp2->data;
		if (ft_strcmp(((t_list *)tmp->data)->data, "A") == 0)
		{
			tmp = tmp->data;
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	ambient = (t_ambient *)arena_alloc(arena, sizeof(t_ambient));
	tmp = tmp->next;
	str = (char *)tmp->data;
	ambient->ratio = ft_atof(str);
	str = (char *)tmp->next->data;
	delimiter = ",";
	vec = (t_vec3){ft_atof(strtok(str, delimiter)), ft_atof(strtok(NULL,
				delimiter)), ft_atof(strtok(NULL, delimiter))};
	ambient->color = color_vec3(vec);
	return (ambient);
}

t_light	*find_light(t_arena *arena, t_list *list)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_vec3	vec;
	t_light	*light;
	char	*str;
	char	*delimiter;

	tmp = list->next;
	while (tmp)
	{
		tmp2 = tmp->data;
		tmp2 = tmp2->data;
		if (ft_strcmp(((t_list *)tmp->data)->data, "L") == 0)
		{
			tmp = tmp->data;
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	light = (t_light *)arena_alloc(arena, sizeof(t_light));
	tmp = tmp->next;
	str = (char *)tmp->data;
	delimiter = ",";
	light->origin = (t_vec3){ft_atof(strtok(str, delimiter)),
		ft_atof(strtok(NULL, delimiter)), ft_atof(strtok(NULL, delimiter))};
	light->ratio = ft_atof((char *)tmp->next->data);
	str = (char *)tmp->next->next->data;
	vec = (t_vec3){ft_atof(strtok(str, delimiter)), ft_atof(strtok(NULL,
				delimiter)), ft_atof(strtok(NULL, delimiter))};
	light->color = color_vec3(vec);
	return (light);
}
