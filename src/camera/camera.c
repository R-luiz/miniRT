/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:18:03 by liguyon           #+#    #+#             */
/*   Updated: 2024/03/29 08:59:05 by vmalassi         ###   ########.fr       */
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

#define M_PI 3.14159265358979323846

void	camera_init_viewport(t_camera *cam, int canvas_width, int canvas_height,
		void *arena)
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
	cam->vp->pixel_00 = vec3_add(vp.upper_left,
			vec3_mul(vec3_add(cam->vp->pixel_du, cam->vp->pixel_dv), 0.5f));
}

t_camera	*camera_create(t_point3 center, t_vec3 direction, float hfov,
		void *arena)
{
	t_camera	*cam;

	cam = arena_alloc(arena, sizeof(*cam));
	cam->center = center;
	cam->look_at = vec3_add(center, direction);
	cam->hfov = hfov;
	return (cam);
}

t_vec3 cylinder_surface_normal(t_object *cy, t_vec3 hit_point, t_vec3 ray_direction)
{
    t_vec3 normal;
    float hit_height;
    t_vec3 c0;

	c0 = vec3_sub(hit_point, cy->center);
    hit_height = vec3_dot(c0, cy->normal);
    if (fabs(hit_height - cy->height) < 1e-5)
        normal = cy->normal;
    else if (fabs(hit_height) < 1e-5)
        normal = vec3_mul(cy->normal, -1);
    else
	{
        t_vec3 closest_point_on_axis = vec3_add(cy->center, vec3_mul(cy->normal, hit_height));
        normal = vec3_normalize(vec3_sub(hit_point, closest_point_on_axis));
	}
    if (vec3_dot(normal, ray_direction) > 0)
        normal = vec3_mul(normal, -1);
    return normal;
}


t_vec3 calc_object(t_render *rd, int i, int j, t_object *obj, t_vec3 final_color, float *min_distance)
{
	t_objects	*objects;
	t_point3	pixel_center;
	t_vec3		ray_direction;
	t_lightray		ray;
	float		distance;
	t_vec3		hit_point;
	t_vec3		normal = {0, 0, 0};
	float		distance_to_light;
	t_list	*object;
	t_vec3		light_color;
	t_vec3		ambient_color;
	float		light_power;
	t_vec3		light_direction;
	t_object	*obj1;
	t_object	*shadow_obj;
	float		diff;

	obj1 = NULL;
	distance_to_light = 0;
	pixel_center = vec3_add(rd->camera->vp->pixel_00,
			vec3_add(vec3_mul(rd->camera->vp->pixel_du, (float)i),
				vec3_mul(rd->camera->vp->pixel_dv, (float)j)));
	ray_direction = vec3_normalize(vec3_sub(pixel_center, rd->camera->center));
	ray = (t_lightray){.origin = rd->camera->center, .direction = ray_direction};
	objects = rd->objects;
	ambient_color = color_to_vec3(objects->ambient->color);
	ambient_color = vec3_mul(ambient_color, objects->ambient->ratio);
	light_direction = vec3_normalize(vec3_sub(objects->light->origin, ray.origin));
	hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, *min_distance));
	distance = obj->hit_dist(obj, ray);
	if (distance > 1e-6 && distance < *min_distance)
	{
		*min_distance= distance;
		obj1 = obj;
		hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
		if (obj->type == 2)
			normal = cylinder_surface_normal(obj, hit_point, ray_direction);
		else if (obj->type == 3)
			normal = vec3_normalize(obj->normal);
		else
			normal = vec3_normalize(vec3_sub(hit_point, obj->center));
		final_color = color_to_vec3(obj->color);
		ray.color = color_vec3(final_color);
		distance_to_light = vec3_length(vec3_sub(hit_point,
					objects->light->origin));
		light_power = objects->light->ratio / (4.0f * M_PI
				* distance_to_light * distance_to_light);
		light_color = vec3_mul(color_to_vec3(objects->light->color),
				light_power);
		light_direction = vec3_normalize(vec3_sub(hit_point,
					objects->light->origin));
		diff = fmax(pow(vec3_dot(normal, light_direction), 2), 0);
		final_color = vec3_mul(final_color, diff);
		final_color = vec3_coloradddue3(final_color, light_color, ambient_color);
	}
	if (final_color.x < 1e-6 && final_color.y < 1e-6 && final_color.z < 1e-6f)
		return (final_color);
	ray.origin = vec3_add(hit_point, vec3_mul(normal, 1e-5f));
	ray.direction = vec3_normalize(vec3_sub(objects->light->origin, hit_point));
	object = rd->objects->all;
	while (object)
	{
		shadow_obj = (t_object *)object->data;
		if (shadow_obj != obj1 && (vec3_dot(ray_direction, light_direction) > 0) && shadow_obj->type != 3)
		{
			distance = shadow_obj->hit_dist(shadow_obj, ray);
			if (distance > 1e-2f && distance < distance_to_light)
			{
				final_color = color_to_vec3(ray.color);
				final_color = vec3_coloradddue(final_color, ambient_color);
				final_color = vec3_mul(final_color, objects->ambient->ratio);
			}
		}
		object = object->next;
	}
	return (final_color);
}

t_vec3 calc_objects(t_render *rd, int i, int j)
{
	t_vec3 final_color;
	t_object *obj;
	t_list	*objects;
	float *min_distance;

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

	rd = (t_render *)vargp;
	int i, j;
	for (j = 0; j < rd->canvas->height; j++)
	{
		for (i = 0; i < rd->canvas->width; i++)
		{
			final_color = calc_objects(rd, i, j);
			color = color_vec3(final_color);
			canvas_draw(rd->canvas, i, j, color);
		}
	}
	return (NULL);
}
