/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:34:02 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/25 02:08:09 by liguyon          ###   ########.fr       */
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

	oc = vec3_sub(ray->origin, center);
	a = vec3_length_squared(ray->direction);
	half_b = vec3_dot(oc, ray->direction);
	c = vec3_length_squared(oc) - radius * radius;
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0.0)
		return (-1.0);
	else
		return ((-half_b - sqrt(discriminant)) / a);
}

static void	render_pixel(t_graphics *grph, t_camera *cam, int i, int j)
{
	t_point3	pxl_center;
	t_color		pxl_col;
	t_vec3		ray_dir;
	t_ray		ray;
	
	pxl_center = vec3_add(vec3_add(cam->pixel00_loc,
		vec3_mul(cam->pixel_delta_u, i)),
		vec3_mul(cam->pixel_delta_v, j));
	ray_dir = vec3_sub(pxl_center, cam->center);
	ray = (t_ray){.origin = cam->center, .direction = ray_dir};
	double t = hit_sphere((t_point3){0, 0, -1}, 0.5, &ray);
	if (t > 0.0)
	{
		t_vec3 n = vec3_unit(vec3_sub(ray_at(ray, t), (t_vec3){0, 0, -1}));
		pxl_col = 0.5 * (double)color_from_rgb(n.x + 1.0, n.y + 1.0, n.z + 1.0);
	}
	else
		pxl_col = 0x000000;
	draw_pixel(grph, i, j, pxl_col);
}

void	render(t_graphics *grph, t_camera *cam)
{
	int	j;
	int	i;

	j = -1;
	while (++j < grph->win_height)
	{
		i = -1;
		while (++i < grph->win_width)
		{
			render_pixel(grph, cam, i, j);
		}
	}
}
