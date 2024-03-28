/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:18:03 by liguyon           #+#    #+#             */
/*   Updated: 2024/03/28 12:47:57 by rluiz            ###   ########.fr       */
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

t_vec3	calc_spheres(t_render *rd, int i, int j)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_objects	*objects;
	t_point3	pixel_center;
	t_vec3		ray_direction;
	t_lightray		ray;
	t_list		*object;
	float		min_distance;
	t_vec3		final_color;
	t_sphere	sphere;
	float		distance;
	t_vec3		hit_point;
	t_vec3		normal;
	float		distance_to_light;
	t_vec3		light_color;
	t_vec3		ambient_color;
	float		light_power;
	t_vec3		light_direction;
	float		diff;

	camera = rd->camera;
	canvas = rd->canvas;
	objects = rd->objects;
	pixel_center = vec3_add(camera->vp->pixel_00,
			vec3_add(vec3_mul(camera->vp->pixel_du, (float)i),
				vec3_mul(camera->vp->pixel_dv, (float)j)));
	ray_direction = vec3_normalize(vec3_sub(pixel_center, camera->center));
	ray = (t_lightray){.origin = camera->center, .direction = ray_direction};
	min_distance = INFINITY;
	final_color = (t_vec3){0, 0, 0};
	ambient_color = color_to_vec3(objects->ambient->color);
	ambient_color = vec3_mul(ambient_color, objects->ambient->ratio);
	object = objects->spheres;
	for (int s = 0; s < objects->sp_count; s++)
	{
		sphere = *(t_sphere *)object->data;
		distance = sphere.hit_dist(&sphere, ray);
		if (distance > 0.0f && distance < min_distance)
		{
			min_distance = distance;
			hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
			normal = vec3_normalize(vec3_sub(hit_point, sphere.center));
			final_color = color_to_vec3(sphere.color);
			ray.color = color_vec3(final_color);
			distance_to_light = vec3_length(vec3_sub(hit_point,
						objects->light->origin));
			light_power = objects->light->ratio / (4.0f * M_PI
					* distance_to_light * distance_to_light);
			light_color = vec3_mul(color_to_vec3(objects->light->color),
					light_power);
			light_direction = vec3_normalize(vec3_sub(objects->light->origin,
						hit_point));
			diff = fmax(pow(vec3_dot(normal, light_direction),2), objects->ambient->ratio);
			final_color = vec3_mul(final_color, diff);
			final_color = vec3_coloradddue(final_color, light_color);
		}
		object = object->next;
	}
	if (final_color.x == 0 && final_color.y == 0 && final_color.z == 0)
		return (final_color);
	ray.origin = hit_point;
	ray.direction = light_direction;
	object = objects->spheres;
	for (int s = 0; s < objects->sp_count; s++)
	{
		sphere = *(t_sphere *)object->data;
		distance = sphere.hit_dist(&sphere, ray);
		if (distance > 0.0f && distance < distance_to_light)
		{
			final_color = vec3_mul(final_color, objects->ambient->ratio / (diff));
			break;
		}
		object = object->next;
	}
	return (final_color);
}

t_vec3	calc_plane(t_render *rd, int i, int j)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_objects	*objects;
	t_point3	pixel_center;
	t_vec3		ray_direction;
	t_lightray		ray;
	t_list		*object;
	float		min_distance;
	t_vec3		final_color;
	t_plane		plane;
	float		distance;
	t_vec3		hit_point;
	t_vec3		normal;
	float		distance_to_light;
	t_vec3		light_color;
	t_vec3		ambient_color;
	float		light_power;
	t_vec3		light_direction;
	float		diff;
	t_list		*objects_hitf;

	camera = rd->camera;
	canvas = rd->canvas;
	objects = rd->objects;
	pixel_center = vec3_add(camera->vp->pixel_00,
			vec3_add(vec3_mul(camera->vp->pixel_du, (float)i),
				vec3_mul(camera->vp->pixel_dv, (float)j)));
	ray_direction = vec3_normalize(vec3_sub(pixel_center, camera->center));
	ray = (t_lightray){.origin = camera->center, .direction = ray_direction};
	min_distance = INFINITY;
	final_color = (t_vec3){0, 0, 0};
	ambient_color = color_to_vec3(objects->ambient->color);
	ambient_color = vec3_mul(ambient_color, objects->ambient->ratio);
	object = objects->planes;
	for (int s = 0; s < objects->pl_count; s++)
	{
		plane = *(t_plane *)object->data;
		distance = plane.hit_dist(&plane, ray);
		if (distance > 0.0f && distance < min_distance)
		{
			min_distance = distance;
			hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
			normal = vec3_normalize(plane.normal);
			final_color = color_to_vec3(plane.color);
			distance_to_light = vec3_length(vec3_sub(hit_point,
						objects->light->origin));
			light_power = objects->light->ratio / (4.0f * M_PI
					* distance_to_light * distance_to_light);
			light_color = vec3_mul(color_to_vec3(objects->light->color), light_power);
			light_direction = vec3_normalize(vec3_sub(hit_point, objects->light->origin));
			diff = fmax(pow(vec3_dot(normal, light_direction), 10), objects->ambient->ratio);
			final_color = vec3_mul(final_color, diff);
			final_color = vec3_coloradddue(final_color, light_color);
			objects_hitf = object->data;
		}
		object = object->next;
	}
	return (final_color);
}

t_vec3 cylinder_surface_normal(void *cylinder, t_vec3 hit_point, t_vec3 ray_direction)
{
    t_cylinder *cy = (t_cylinder *)cylinder;
    t_vec3 normal;
    float hit_height;

    // Compute the projection length of the hit point on the cylinder's axis
    t_vec3 CO = vec3_sub(hit_point, cy->center);
    hit_height = vec3_dot(CO, cy->normal);

    // Check if the hit is on the top cap
    if (fabs(hit_height - cy->height) < 1e-8) {
        normal = cy->normal; // Top cap normal is the same as cylinder's axis direction
    }
    // Check if the hit is on the bottom cap
    else if (fabs(hit_height) < 1e-8) {
        normal = vec3_mul(cy->normal, -1); // Bottom cap normal is opposite to the cylinder's axis direction
    }
    // Otherwise, hit is on the cylindrical surface
    else {
        t_vec3 closest_point_on_axis = vec3_add(cy->center, vec3_mul(cy->normal, hit_height));
        normal = vec3_normalize(vec3_sub(hit_point, closest_point_on_axis));
    }

    // Ensure the normal is correctly oriented with respect to the incoming ray
    if (vec3_dot(normal, ray_direction) > 0) {
        normal = vec3_mul(normal, -1);
    }

    return normal;
}

t_vec3	calc_cylinders(t_render *rd, int i, int j)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_objects	*objects;
	t_point3	pixel_center;
	t_vec3		ray_direction;
	t_lightray		ray;
	t_list		*object;
	float		min_distance;
	t_vec3		final_color;
	t_cylinder	cylinder;
	float		distance;
	t_vec3		hit_point;
	t_vec3		normal;
	float		distance_to_light;
	t_vec3		light_color;
	t_vec3		ambient_color;
	float		light_power;
	t_vec3		light_direction;
	float		diff;

	camera = rd->camera;
	canvas = rd->canvas;
	objects = rd->objects;
	pixel_center = vec3_add(camera->vp->pixel_00,
			vec3_add(vec3_mul(camera->vp->pixel_du, (float)i),
				vec3_mul(camera->vp->pixel_dv, (float)j)));
	ray_direction = vec3_normalize(vec3_sub(pixel_center, camera->center));
	ray = (t_lightray){.origin = camera->center, .direction = ray_direction};
	min_distance = INFINITY;
	final_color = (t_vec3){0, 0, 0};
	ambient_color = color_to_vec3(objects->ambient->color);
	ambient_color = vec3_mul(ambient_color, objects->ambient->ratio);
	object = objects->cylinders;
	for (int s = 0; s < objects->cy_count; s++)
	{
		cylinder = *(t_cylinder *)object->data;
		distance = cylinder.hit_dist(&cylinder, ray);
		if (distance > 0.00001f && distance < min_distance)
		{
			min_distance = distance;
			hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
			normal = cylinder_surface_normal(&cylinder, hit_point, ray_direction);
			final_color = color_to_vec3(cylinder.color);
			ray.color = color_vec3(final_color);
			distance_to_light = vec3_length(vec3_sub(hit_point,
						objects->light->origin));
			light_power = objects->light->ratio / (4.0f * M_PI
					* distance_to_light * distance_to_light);
			light_color = vec3_mul(color_to_vec3(objects->light->color),
					light_power);
			light_direction = vec3_normalize(vec3_sub(objects->light->origin,
						hit_point));
			diff = fmax(pow(vec3_dot(normal, light_direction), 2), 0);
			final_color = vec3_mul(final_color, diff);
			final_color = vec3_coloradddue3(final_color, light_color, ambient_color);
		}
		object = object->next;
	}
	if (final_color.x < 1e-6 && final_color.y < 1e-6 && final_color.z < 1e-6)
		return (final_color);
	ray.origin = hit_point;
	ray.direction = light_direction;
	ray.color = color_vec3(final_color);
	object = objects->cylinders;
	for (int s = 0; s < objects->cy_count; s++)
	{
		cylinder = *(t_cylinder *)object->data;
		distance = cylinder.hit_dist(&cylinder, ray);
		if (distance > 0.00001f && distance < min_distance)
		{
			min_distance = distance;
			hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
			normal = cylinder_surface_normal(&cylinder, hit_point, ray_direction);
			diff = fmax(pow(vec3_dot(normal, light_direction), 2), 0);
			final_color = vec3_mul(final_color, diff);
			final_color = vec3_coloradddue3(final_color, light_color, ambient_color);
		}
		object = object->next;
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
	final_color = (t_vec3){0, 0, 0};
	for (j = 0; j < rd->canvas->height; j++)
	{
		for (i = 0; i < rd->canvas->width; i++)
		{
			// final_color = calc_plane(rd, i, j);
			// final_color = calc_spheres(rd, i, j);
			final_color = calc_cylinders(rd, i, j);
			color = color_vec3(final_color);
			canvas_draw(rd->canvas, i, j, color);
		}
	}
	return (NULL);
}
