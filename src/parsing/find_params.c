/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:47:05 by rluiz             #+#    #+#             */
/*   Updated: 2024/04/08 15:03:54 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "camera/camera.h"

t_camera	*find_camera2(t_arena *arena, t_list *tmp, char *str,
t_camera *camera)
{
	if (!tmp->next)
		free_and_exit_error(arena, "Invalid camera parameters");
	str = (char *)tmp->next->data;
	if (!is_coordinates(str))
		free_and_exit_error(arena, "Invalid camera direction");
	camera->look_at = (t_vec3){safe_atof(arena, ft_strtok(str, ",")),
		safe_atof(arena, ft_strtok(NULL, ",")),
		safe_atof(arena, ft_strtok(NULL, ","))};
	if (!tmp->next || !tmp->next->next)
		free_and_exit_error(arena, "Invalid camera parameters");
	str = str_is_float(arena, (char *)tmp->next->next->data, "Invalid FOV");
	camera->hfov = safe_atof(arena, str);
	return (camera);
}

t_camera	*find_camera(t_arena *arena, t_list *list, char *str)
{
	t_list		*tmp;
	t_camera	*camera;

	tmp = find_id_line(list, "C");
	if (!tmp)
		free_and_exit_error(arena, "No camera found");
	camera = (t_camera *)arena_alloc(arena, sizeof(t_camera));
	tmp = tmp->next;
	if (!tmp)
		free_and_exit_error(arena, "Invalid camera parameters");
	str = (char *)tmp->data;
	if (!is_coordinates(str))
		free_and_exit_error(arena, "Invalid camera coordinates");
	camera->center = (t_vec3){safe_atof(arena, ft_strtok(str, ",")),
		safe_atof(arena, ft_strtok(NULL, ",")),
		safe_atof(arena, ft_strtok(NULL, ","))};
	return (find_camera2(arena, tmp, str, camera));
}

t_ambient	*find_ambient(t_arena *arena, t_list *list, char *str)
{
	t_list		*tmp;
	t_vec3		vec;
	t_ambient	*ambient;

	tmp = find_id_line(list, "A");
	if (!tmp)
		free_and_exit_error(arena, "No ambient light found");
	ambient = (t_ambient *)arena_alloc(arena, sizeof(t_ambient));
	tmp = tmp->next;
	if (!tmp)
		free_and_exit_error(arena, "Invalid ambient parameters");
	str = str_is_float(arena, (char *)tmp->data, "Invalid ambient ratio");
	ambient->ratio = safe_atof(arena, str);
	if (!float_in_range(ambient->ratio, 0, 1))
		free_and_exit_error(arena, "Invalid ambient ratio");
	str = (char *)tmp->next->data;
	if (!is_rgb(str))
		free_and_exit_error(arena, "Invalid ambient color");
	vec = extract_rgb(arena, str, "Invalid ambient color");
	ambient->color = color_vec3(vec);
	return (ambient);
}

t_light	*find_light2(t_arena *arena, t_list	*tmp, t_light *light)
{
	t_vec3	color;
	char	*str;

	str = str_is_float(arena, (char *)tmp->data, "Invalid light ratio");
	light->ratio = safe_atof(arena, str);
	if (!float_in_range(light->ratio, 0, 1))
		free_and_exit_error(arena, "Invalid light ratio");
	if (!tmp->next)
		free_and_exit_error(arena, "Invalid light parameters");
	str = (char *)tmp->next->data;
	if (!is_rgb(str))
		free_and_exit_error(arena, "Invalid light color");
	color = extract_rgb(arena, str, "Invalid light color");
	light->color = color_int(color.x, color.y, color.z);
	return (light);
}

t_light	*find_light(t_arena *arena, t_list *list, char *str)
{
	t_list	*tmp;
	t_light	*light;

	tmp = find_id_line(list, "L");
	if (!tmp)
		free_and_exit_error(arena, "No light found");
	light = (t_light *)arena_alloc(arena, sizeof(t_light));
	tmp = tmp->next;
	if (!tmp)
		free_and_exit_error(arena, "Invalid light parameters");
	str = (char *)tmp->data;
	if (!is_coordinates(str))
		free_and_exit_error(arena, "Invalid light coordinates");
	light->origin = (t_vec3){safe_atof(arena, ft_strtok(str, ",")),
		safe_atof(arena, ft_strtok(NULL, ",")),
		safe_atof(arena, ft_strtok(NULL, ","))};
	if (!tmp->next)
		free_and_exit_error(arena, "Invalid light parameters");
	tmp = tmp->next;
	return (find_light2(arena, tmp, light));
}
