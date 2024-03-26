/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:47:05 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/26 05:57:28 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "camera/camera.h"

t_camera	*find_camera(t_arena *arena, t_list *list, char *str)
{
	t_list		*tmp;
	t_camera	*camera;

	tmp = list->next;
	while (tmp)
	{
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
	camera->center = (t_vec3){ft_atof(strtok(str, ",")),
		ft_atof(strtok(NULL, ",")), ft_atof(strtok(NULL, ","))};
	str = (char *)tmp->next->data;
	camera->look_at = (t_vec3){ft_atof(strtok(str, ",")),
		ft_atof(strtok(NULL, ",")), ft_atof(strtok(NULL, ","))};
	camera->hfov = ft_atof((char *)tmp->next->next->data);
	return (camera);
}

t_ambient	*find_ambient(t_arena *arena, t_list *list, char *str)
{
	t_list		*tmp;
	t_vec3		vec;
	t_ambient	*ambient;

	tmp = list->next;
	while (tmp)
	{
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
	vec = (t_vec3){ft_atof(strtok(str, ",")) / 255, ft_atof(strtok(NULL,
				",")) / 255, ft_atof(strtok(NULL, ",")) / 255};
	ambient->color = color_vec3(vec);
	return (ambient);
}

t_light	*find_light(t_arena *arena, t_list *list, char *str)
{
	t_list	*tmp;
	t_light	*light;

	tmp = list->next;
	while (tmp)
	{
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
	light->origin = (t_vec3){ft_atof(strtok(str, ",")),
		ft_atof(strtok(NULL, ",")), ft_atof(strtok(NULL, ","))};
	light->ratio = ft_atof((char *)tmp->next->data);
	str = (char *)tmp->next->next->data;
	light->color = color_int(ft_atoi(ft_strtok(str, ",")),
			ft_atoi(ft_strtok(NULL, ",")), ft_atoi(ft_strtok(NULL, ",")));
	return (light);
}
