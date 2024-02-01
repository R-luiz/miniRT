/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:18:03 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/01 16:39:32 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./camera.h"
#include "canvas/canvas.h"
#include "engine/engine.h"
#include "ray.h"
#include "libft.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

void		camera_init_viewport(
	t_camera *cam, int canvas_width, int canvas_height, void *arena)
{
	float		focal_length;
	t_vec3		cam_u;
	t_vec3		cam_v;
	t_vec3		cam_w;
	t_vp_helper	vp;

	cam->vp = arena_alloc(arena, sizeof(*cam->vp));
	focal_length = vec3_length(vec3_sub(cam->look_at, cam->center));
	vp.width = 2 * focal_length * tanf(to_rad(cam->hfov) / 2);
	vp.height = vp.width * ((float)canvas_height / canvas_width);
	cam_w = vec3_normalize(vec3_add(cam->center, cam->look_at));
	cam_u = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, cam_w));
	cam_v = vec3_cross(cam_w, cam_u);
	vp.u = vec3_mul(cam_u, vp.width);
	vp.v = vec3_mul(cam_v, -vp.height);
	cam->vp->pixel_du = vec3_div(vp.u, canvas_width);
	cam->vp->pixel_dv = vec3_div(vp.v, canvas_height);
	vp.upper_left = vec3_add(cam->center, vec3_mul(cam_w, focal_length));
	vp.upper_left = vec3_sub(vp.upper_left, vec3_div(vp.u, 2));
	vp.upper_left = vec3_sub(vp.upper_left, vec3_div(vp.v, 2));
	cam->vp->pixel_00 = vec3_add(
		vp.upper_left, vec3_mul(
			vec3_add(cam->vp->pixel_du, cam->vp->pixel_dv), 0.5f));
}

t_camera	*camera_create(
	t_point3 center, t_vec3 direction, float hfov, void *arena)
{
	t_camera	*cam;

	cam = arena_alloc(arena, sizeof(*cam));
	cam->center = center;
	cam->look_at = vec3_add(center, direction);
	cam->hfov = hfov;
	return (cam);
}

bool	hit_sphere(t_point3 center, float radius, t_ray *ray)
{
	t_vec3	oc = vec3_sub(ray->origin, center);
	float a = vec3_dot(ray->direction, ray->direction);
	float b = 2 * vec3_dot(oc, ray->direction);
	float c = vec3_dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

void	*camera_render(void *vargp)
{
	t_render	*rd;
	t_camera	*camera;
	t_canvas	*canvas;
	int			i;
	int			j;
	t_color		c;

	rd = (t_render *)vargp;
	camera = rd->camera;
	canvas = rd->canvas;
	j = -1;
	while (++j < canvas->height)
	{
		i = -1;
		while (++i < canvas->width)
		{
			if (!engine_is_running(rd->engine))
				return (NULL);
			t_point3 pixel_center = vec3_add(camera->vp->pixel_00, vec3_mul(camera->vp->pixel_du, i));
			pixel_center = vec3_add(pixel_center, vec3_mul(camera->vp->pixel_dv, j));
			t_vec3 ray_dir = vec3_sub(pixel_center, camera->center);
			t_ray ray = (t_ray){.origin = camera->center, .direction = ray_dir};
			if (hit_sphere((t_point3){0, 0, 2}, 0.2, &ray))
				c = 0xff0000;
			else
				c = 0;
			canvas_draw(canvas, i, j, c);
		}
	}
	printf("finished rendering scene\n");
	return (NULL);
}
