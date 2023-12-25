/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:34:02 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/25 05:59:19 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double	hit_sphere(t_point3 center, double radius, t_ray *ray)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray->origin, center);
	a = vec3_length_squared(ray->direction);
	half_b = vec3_dot(oc, ray->direction);
	c = vec3_length_squared(oc) - radius * radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-half_b - sqrt(discriminant)) / a);
}

t_color	ray_color(t_ray *ray)
{
	if (hit_sphere((t_point3){0, 0, -1}, 0.2, ray) > 0)
		return (0xff0000);
	else if (hit_sphere((t_point3){-0.75, 0.4, -1}, 0.2, ray) > 0)
		return (0xff00ff);
	else if (hit_sphere((t_point3){0.75, -0.2, -1}, 0.2, ray) > 0)
		return (0x00ffff);
	else
		return (COLOR_BG);
}

static void	render_pixel(t_graphics *grph, t_camera *cam, int i, int j)
{
	t_point3	pxl_center;
	t_vec3		ray_dir;
	t_ray		ray;
	t_color		ray_col;

	pxl_center = vec3_add(
			vec3_add(cam->pixel00_loc, vec3_mul(cam->pixel_delta_u, i)),
			vec3_mul(cam->pixel_delta_v, j));
	ray_dir = vec3_sub(pxl_center, cam->center);
	ray = (t_ray){.origin = cam->center, .direction = ray_dir};
	ray_col = ray_color(&ray);
	if (ray_col != COLOR_BG)
	{
		pthread_mutex_lock(&grph->canvas->mutex);
		draw_pixel(grph, i, j, ray_col);
		pthread_mutex_unlock(&grph->canvas->mutex);
	}
}

typedef struct s_targs
{
	t_graphics	*grph;
	t_camera	*cam;
	int			j;
}	t_targs;

void	*thread_routine(void *vargp)
{
	t_targs	*targs = (t_targs *)vargp;
	t_graphics	*grph = targs->grph;
	t_camera	*cam = targs->cam;
	int			j = targs->j;
	for (int i = 0; i < grph->win_width; ++i)
		render_pixel(grph, cam, i, j);
	return (NULL);
}

#define N_THREAD 9

void	render(t_graphics *grph, t_camera *cam)
{
	int	j;

	j = 0;
	while (j < grph->win_height)
	{
		pthread_t threads[N_THREAD];
		for (int i = 0; i < N_THREAD; ++i)
		{
			t_targs args = {grph, cam, j};
			pthread_create(&threads[i], NULL, thread_routine, &args);
			++j;
		}
		for (int i = 0; i < N_THREAD; ++i)
			pthread_join(threads[i], NULL);
	}
}
