/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:37:38 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:24:43 by vmalassi         ###   ########.fr       */
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

t_vec3	get_normal(t_object *obj, t_vec3 ray_direction, t_vec3 hit_point)
{
	t_vec3	normal;

	if (obj->type == 2)
		normal = cylinder_surface_normal(obj, hit_point, ray_direction);
	else if (obj->type == 3)
		normal = vec3_normalize(obj->normal);
	else
		normal = vec3_normalize(vec3_sub(hit_point, obj->center));
	return (normal);
}

t_vec3	compute_diffraction(t_object *obj, t_vec3 final_color, t_vec3 normal,
t_vec3 light_direction)
{
	float	diff;

	if (obj->type == 3)
		diff = fmax(vec3_dot(normal, light_direction), 0);
	else
		diff = acosf(vec3_dot(normal, light_direction)) / M_PI;
	final_color = vec3_mul(final_color, pow(diff, 3));
	return (final_color);
}

//0 t_render *rd,1 t_object *obj,2 t_vec3 hit_point,3 t_vec3 ray_direction,4 
//t_vec3 ambient_color,5 t_objects *objects
t_vec3	compute_lightning_shading(t_vec3 final_color, t_vec3 light_direction,
t_lightray ray, void *p[6])
{
	t_vec3		normal;
	float		distance_to_light;

	normal = get_normal((t_object *)p[1], *((t_vec3 *)p[3]), *((t_vec3 *)p[2]));
	final_color = color_to_vec3(((t_object *)p[1])->color);
	ray.color = color_vec3(final_color);
	light_direction = vec3_normalize(vec3_sub(*((t_vec3 *)p[2]),
				((t_objects *)p[5])->light->origin));
	distance_to_light = vec3_length(vec3_sub(*((t_vec3 *)p[2]),
				((t_objects *)p[5])->light->origin));
	final_color = compute_diffraction((t_object *)p[1], final_color, normal,
			light_direction);
	final_color = vec3_coloradddue3(final_color, vec3_mul(color_to_vec3((
						(t_objects *)p[5])->light->color), (
					(t_objects *)p[5])->light->ratio / (4.0f * M_PI
					* distance_to_light * distance_to_light)),
			*((t_vec3 *)p[4]));
	ray.origin = vec3_add(*((t_vec3 *)p[2]), vec3_mul(normal, 1e-6f));
	ray.direction = vec3_normalize(vec3_sub(((t_objects *)p[5])->light->origin,
				*((t_vec3 *)p[2])));
	final_color = iter_objects((void *[5]){(t_render *)p[0], (t_object *)p[1],
			&ray, &distance_to_light, (t_vec3 *)p[4]}, final_color);
	return (final_color);
}

t_vec3	calc_object(t_render *rd, void *params[3], t_object *obj,
float *min_distance)
{
	t_objects	*objects;
	t_lightray	ray;
	float		distance;
	t_vec3		vecs[4];
	t_vec3		final_color;

	final_color = *((t_vec3 *)params[0]);
	vecs[0] = vec3_normalize(vec3_sub(get_pixel_center(rd->camera,
					*((int *)params[1]), *((int *)params[2])),
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
		final_color = compute_lightning_shading(final_color, vecs[2], ray,
				(void *[6]){rd, obj, &vecs[3], &vecs[0], &vecs[1], objects});
	}
	return (final_color);
}

//0 t_render *rd,1 t_object *obj,2 t_vec3 hit_point,3 t_vec3 ray_direction,
//4 t_vec3 ambient_color,5 t_objects *objects
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
		final_color = calc_object(rd, (void *[3]){&final_color, &i, &j},
				obj, min_distance);
		objects = objects->next;
	}
	return (final_color);
}
