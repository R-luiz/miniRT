/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:44:00 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/25 02:02:39 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

static int	inputs_process_structure(t_data *data)
{
	mlx_loop_end(data->grph->mlx_ptr);
	return (EXIT_SUCCESS);
}

static void	inputs_process_keypress_camera(int keycode, t_data *data)
{
	if (keycode == XK_Left)
		data->cam->center = vec3_sub(data->cam->center, (t_vec3){0.1, 0, 0});
	else if (keycode == XK_Right)
		data->cam->center = vec3_add(data->cam->center, (t_vec3){0.1, 0, 0});
	else if (keycode == XK_Up)
		data->cam->center = vec3_add(data->cam->center, (t_vec3){0, 0.1, 0});
	else if (keycode == XK_Down)
		data->cam->center = vec3_sub(data->cam->center, (t_vec3){0, 0.1, 0});
	else if (keycode == XK_Page_Up)
		data->cam->center = vec3_sub(data->cam->center, (t_vec3){0, 0, 0.1});
	else if (keycode == XK_Page_Down)
		data->cam->center = vec3_add(data->cam->center, (t_vec3){0, 0, 0.1});
	else if (keycode == XK_r)
	{
		data->cam->center = data->cam->center_default;
		data->cam->hfov = data->cam->hfov_default;
	}
	camera_init(data->cam, data->cam->center, data->cam->hfov);
}

static int	inputs_process_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->grph->mlx_ptr);
	else if (keycode == XK_Left || keycode == XK_Right || keycode == XK_Up
		|| keycode == XK_Down || keycode == XK_Page_Up
		|| keycode == XK_Page_Down || keycode == XK_r)
		inputs_process_keypress_camera(keycode, data);
	return (EXIT_SUCCESS);
}

void	inputs_bind(t_data *data)
{
	mlx_hook(data->grph->win_ptr, DestroyNotify, StructureNotifyMask,
		inputs_process_structure, data);
	mlx_hook(data->grph->win_ptr, KeyPress, KeyPressMask,
		inputs_process_keypress, data);
	// mlx_hook(data->grph->win_ptr, ButtonPress, ButtonPressMask,
	// 	inputs_process_mpress, data);
	// mlx_hook(data->grph->win_ptr, ButtonRelease, ButtonReleaseMask,
	// 	inputs_process_mrelease, data);
}
