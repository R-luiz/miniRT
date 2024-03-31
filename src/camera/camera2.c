/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:37:38 by vmalassi          #+#    #+#             */
/*   Updated: 2024/03/31 20:33:27 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./camera.h"
#include "canvas/canvas.h"
#include "engine/engine.h"
#include "objects/objects.h"
#include "libft.h"
#include "ray.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

t_vec3	compute_lightning_shading(t_render *rd, t_object *obj, t_lightray ray, t_vec3 ray_direction, t_vec3 final_color, t_vec3 light_direction, t_vec3 ambient_color, t_objects *objects, t_vec3 hit_point)
{
	t_vec3		normal;
	float		distance_to_light;
	float		diff;

	if (obj->type == 2)
		normal = cylinder_surface_normal(obj, hit_point, ray_direction);
	else if (obj->type == 3)
		normal = vec3_normalize(obj->normal);
	else
		normal = vec3_normalize(vec3_sub(hit_point, obj->center));
	final_color = color_to_vec3(obj->color);
	ray.color = color_vec3(final_color);
	light_direction = vec3_normalize(vec3_sub(hit_point,
				objects->light->origin));
	distance_to_light = vec3_length(vec3_sub(hit_point,
				objects->light->origin));
	if (obj->type == 3)
		diff = fmax(vec3_dot(normal, light_direction), 0);
	else
		diff = acosf(vec3_dot(normal, light_direction)) / M_PI;
	final_color = vec3_mul(final_color, pow(diff, 3));
	final_color = vec3_coloradddue3(final_color,
			vec3_mul(color_to_vec3(objects->light->color),
				objects->light->ratio / (4.0f * M_PI
					* distance_to_light * distance_to_light)), ambient_color);
	ray.origin = vec3_add(hit_point, vec3_mul(normal, 1e-6f));
	ray.direction = vec3_normalize(vec3_sub(objects->light->origin, hit_point));
	final_color = iter_objects((void *[5]){rd, obj, &ray, &distance_to_light,
			&ambient_color}, final_color);
	return (final_color);
}

t_vec3	calc_object(t_render *rd, int i, int j, t_object *obj, t_vec3 final_color, float *min_distance)
{
	t_objects	*objects;
	t_lightray	ray;
	float		distance;
	t_vec3		vecs[4];

	vecs[0] = vec3_normalize(vec3_sub(get_pixel_center(rd->camera, i, j),
				rd->camera->center));
	ray = (t_lightray){.origin = rd->camera->center, .direction = vecs[0]};
	objects = rd->objects;
	vecs[1] = color_to_vec3(objects->ambient->color);
	vecs[1] = vec3_mul(vecs[1], objects->ambient->ratio);
	vecs[2] = vec3_normalize(vec3_sub(objects->light->origin, ray.origin));
	distance = obj->hit_dist(obj, ray);
	if (distance > 1e-6 && distance < *min_distance)
	{
		*min_distance = distance;
		vecs[3] = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
		final_color = compute_lightning_shading(rd, obj, ray, vecs[0],
				final_color, vecs[2], vecs[1], objects, vecs[3]);
	}
	return (final_color);
}

t_vec3	calc_objects(t_render *rd, int i, int j)
{
	t_vec3		final_color;
	t_object	*obj;
	t_list		*objects;
	float		*min_distance;

	objects = rd->objects->all;
	min_distance = arena_alloc(rd->arena, sizeof(*min_distance));
	*min_distance = INFINITY;
	final_color = (t_vec3){0, 0, 0};
	while (objects)
	{
		obj = (t_object *)objects->data;
		final_color = calc_object(rd, i, j, obj, final_color, min_distance);
		objects = objects->next;
	}
	return (final_color);
}

void	*camera_render(void *vargp)
{
	t_render	*rd;
	t_color		color;
	t_vec3		final_color;
	int			i;
	int			j;

	rd = (t_render *)vargp;
	j = 0;
	while (j < rd->canvas->height)
	{
		i = 0;
		while (i < rd->canvas->width)
		{
			final_color = calc_objects(rd, i, j);
			color = color_vec3(final_color);
			canvas_draw(rd->canvas, i, j, color);
			i++;
		}
		j++;
	}
	return (NULL);
}
