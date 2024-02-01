/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:47:05 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/01 17:17:35 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

float ft_atof(char *str)
{
	float res;
	float sign;
	float power;

	res = 0;
	sign = 1;
	power = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str && *str != ',')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str && *str != ',')
		{
			res = res * 10 + (*str - '0');
			power *= 10;
			str++;
		}
	}
	return (sign * res / power);
}

t_camera *find_camera(t_arena *arena, t_list *list)
{
	t_list *tmp;
	t_list *tmp2;
	t_camera *camera;
	char *str;
	char *delimiter;

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
	camera->center = (t_vec3){ft_atof(strtok(str, delimiter)), ft_atof(strtok(NULL, delimiter)), ft_atof(strtok(NULL, delimiter))};
	str = (char *)tmp->next->data;
	camera->look_at = (t_vec3){ft_atof(strtok(str, delimiter)), ft_atof(strtok(NULL, delimiter)), ft_atof(strtok(NULL, delimiter))};
	camera->hfov = ft_atof((char *)tmp->next->next->data);
	return (camera);
}
