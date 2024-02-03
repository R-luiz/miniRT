/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:18:03 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/03 16:37:34 by rluiz            ###   ########.fr       */
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

float	hit_sphere_distance(t_point3 center, float radius, t_ray *ray)
{
	t_vec3	oc = vec3_sub(ray->origin, center);
	float a = vec3_dot(ray->direction, ray->direction);
	float b = 2 * vec3_dot(oc, ray->direction);
	float c = vec3_dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (-b - sqrtf(discriminant)) / (2 * a);
}

void	*camera_render(void *vargp)
{
	t_render	*rd = (t_render *)vargp;
	t_camera	*camera = rd->camera;
	t_canvas	*canvas = rd->canvas;
	t_objects	*objects = rd->objects;
	int			i, j;
	t_color		color;

	printf("camera center: %f %f %f\n", camera->center.x, camera->center.y, camera->center.z);
	for (j = 0; j < canvas->height; j++) {
		for (i = 0; i < canvas->width; i++) {
			if (!engine_is_running(rd->engine)) {
				return NULL;
			}

			t_point3 pixel_center = vec3_add(
				camera->vp->pixel_00, 
				vec3_add(
					vec3_mul(camera->vp->pixel_du, (float)i), 
					vec3_mul(camera->vp->pixel_dv, (float)j)
				)
			);

			t_vec3 ray_direction = vec3_normalize(vec3_sub(pixel_center, camera->center));
			t_ray ray = { .origin = camera->center, .direction = ray_direction };

			float min_distance = INFINITY;
			t_vec3 final_color = {0, 0, 0};

			for (int s = 0; s < objects->sp_count; s++) {
				t_sphere sphere = *(t_sphere *)objects->spheres->data;
				float distance = hit_sphere_distance(sphere.center, sphere.diameter/2, &ray);
				if (distance > 0.0f && distance < min_distance) {
					min_distance = distance;
					t_vec3 hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
					t_vec3 normal = vec3_normalize(vec3_sub(hit_point, sphere.center));
					final_color = vec3_mul(vec3_add(vec3_mul(normal, 0.5f), (t_vec3){0.5f, 0.5f, 0.5f}), 255.0f);
				}
			}

			if (min_distance == INFINITY) {
				// Background gradient
				float t = 0.5f * (ray_direction.y + 1.0f);
				final_color = vec3_add(
					vec3_mul((t_vec3){1.0f, 1.0f, 1.0f}, (1.0f - t)),
					vec3_mul((t_vec3){0.5f, 0.7f, 1.0f}, t)
				);
				final_color = vec3_mul(final_color, 255.0f);
			}

			color = ((int)final_color.x << 16) | ((int)final_color.y << 8) | (int)final_color.z;
			canvas_draw(canvas, i, j, color);
		}
	}

	printf("finished rendering scene\n");
	return NULL;
}
