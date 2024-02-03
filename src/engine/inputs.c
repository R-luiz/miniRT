/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:44:00 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/03 18:11:29 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./engine.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

static void	loop_end(t_engine *eng)
{
	pthread_mutex_lock(&eng->mut);
	eng->is_running = false;
	mlx_loop_end(eng->grph->mlx_ptr);
	pthread_mutex_unlock(&eng->mut);
}

static int	inputs_process_structure(t_engine *eng)
{
	loop_end(eng);
	return (0);
}

static int	inputs_process_keypress(int keycode, t_render *rd)
{
	t_camera	*camera;
	float		move_speed;

	camera = rd->camera;
	move_speed = 0.01f;
	if (keycode == XK_Escape)
		loop_end(rd->engine);
	if (keycode == XK_w)
		camera->center.y -= move_speed;
	if (keycode == XK_a)
		camera->center.x += move_speed;
	if (keycode == XK_s)
		camera->center.y += move_speed;
	if (keycode == XK_d)
		camera->center.x -= move_speed;
	return (0);
}

static int	inputs_process_mouse(int button, int x, int y, t_render *rd)
{
	t_camera	*camera;
	float		zoom_speed;
	float		aspect_ratio;
	float		ndc_x;
	float		ndc_y;
	t_vec3		ray_dir;

	camera = rd->camera;
	zoom_speed = 0.05f;
	aspect_ratio = (float)rd->canvas->width / (float)rd->canvas->height;
	ndc_x = (2.0f * x) / rd->canvas->width - 1.0f;
	ndc_y = 1.0f - (2.0f * y) / rd->canvas->height;
	ndc_x *= -1;
	ndc_y *= -1;
	ray_dir = vec3_normalize((t_vec3){ndc_x * aspect_ratio, ndc_y, -1.0f});
	if (button == 4)
		camera->center = vec3_add(camera->center, vec3_mul(ray_dir,
					zoom_speed));
	else if (button == 5)
		camera->center = vec3_sub(camera->center, vec3_mul(ray_dir,
					zoom_speed));
	return (0);
}

void	inputs_bind(t_render *rd)
{
	t_engine	*eng;

	eng = rd->engine;
	mlx_hook(eng->grph->win_ptr, DestroyNotify, StructureNotifyMask,
		inputs_process_structure, eng);
	mlx_hook(eng->grph->win_ptr, KeyPress, KeyPressMask,
		inputs_process_keypress, rd);
	mlx_hook(eng->grph->win_ptr, ButtonPress, ButtonPressMask,
		inputs_process_mouse, rd);
}
