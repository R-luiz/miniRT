/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:18:03 by liguyon           #+#    #+#             */
/*   Updated: 2024/03/05 16:00:48 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./camera.h"
#include "canvas/canvas.h"
#include "engine/engine.h"
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

bool	hit_sphere(t_point3 center, float radius, t_ray *ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(ray->origin, center);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2 * vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

float	hit_sphere_distance(t_point3 center, float radius, t_ray *ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(ray->origin, center);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2 * vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant <= 0)
		return (-1);
	return (-b - sqrtf(discriminant)) / (2 * a);
}

static int solve_quadratic(float A, float B, float C, float *t0, float *t1) {
    float discriminant = B * B - 4 * A * C;
    if (discriminant < 0) return 0; // No real roots
    float sqrtDiscriminant = sqrtf(discriminant);
    *t0 = (-B - sqrtDiscriminant) / (2 * A);
    *t1 = (-B + sqrtDiscriminant) / (2 * A);
    if (*t0 > *t1) {
        float temp = *t0;
        *t0 = *t1;
        *t1 = temp;
    }
    return discriminant == 0 ? 1 : 2; // 1 or 2 real roots
}

// Calculates the distance from the ray origin to the cylinder intersection point
float hit_cylinder_distance(t_point3 center, t_vec3 axis, float radius, t_ray *ray) {
    t_vec3 CO = vec3_sub(ray->origin, center); // Vector from cylinder center to ray origin
    t_vec3 D = ray->direction; // Ray direction
    t_vec3 A = vec3_sub(D, vec3_mul(axis, vec3_dot(D, axis))); // Component of D perpendicular to axis
    t_vec3 B = vec3_sub(CO, vec3_mul(axis, vec3_dot(CO, axis))); // Component of CO perpendicular to axis

    // Quadratic coefficients
    float a = vec3_dot(A, A);
    float b = 2 * vec3_dot(A, B);
    float c = vec3_dot(B, B) - radius * radius;

    // Solving the quadratic equation for t
    float t0, t1;
    if (solve_quadratic(a, b, c, &t0, &t1) == 0) return -1; // No intersection

    // Check for cylinder's height limit here if necessary

    return t0 >= 0 ? t0 : -1;
}

t_vec3 calc_cylinder(t_render *rd, int i, int j)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_objects	*objects;
	t_point3	pixel_center;
	t_vec3		ray_direction;
	t_ray		ray;
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
	t_list		*objects_hitf;

	camera = rd->camera;
	canvas = rd->canvas;
	objects = rd->objects;
	pixel_center = vec3_add(camera->vp->pixel_00,
			vec3_add(vec3_mul(camera->vp->pixel_du, (float)i),
				vec3_mul(camera->vp->pixel_dv, (float)j)));
	ray_direction = vec3_normalize(vec3_sub(pixel_center, camera->center));
	ray = (t_ray){.origin = camera->center, .direction = ray_direction};
	min_distance = INFINITY;
	final_color = (t_vec3){0, 0, 0};
	ambient_color = color_to_vec3(objects->ambient->color);
	ambient_color = vec3_mul(ambient_color, objects->ambient->ratio);
	object = objects->cylinders;
	for (int s = 0; s < objects->cy_count; s++)
	{
		cylinder = *(t_cylinder *)object->data;
		distance = hit_cylinder_distance(cylinder.center, cylinder.normal, cylinder.diameter / 2,
				&ray);
		if (distance > 0.0f && distance < min_distance)
		{
			min_distance = distance;
			hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
			normal = vec3_normalize(vec3_sub(hit_point, cylinder.center));
			final_color = color_to_vec3(cylinder.color);
			distance_to_light = vec3_length(vec3_sub(hit_point,
						objects->light->origin));
			light_power = objects->light->ratio / (4.0f * M_PI
					* distance_to_light * distance_to_light);
			light_color = vec3_mul(color_to_vec3(objects->light->color),
					light_power);
			light_direction = vec3_normalize(vec3_sub(objects->light->origin,
						hit_point));
			diff = fmax(vec3_dot(normal, light_direction), 0.0);
			final_color = vec3_mul(final_color, diff);
			final_color = vec3_coloradddue(final_color, light_color);
			objects_hitf = object->data;
		}
		object = object->next;
	}
	ray.origin = hit_point;
	ray.direction = light_direction;
	object = objects->cylinders;
	for (int s = 0; s < objects->cy_count; s++)
	{
		cylinder = *(t_cylinder *)object->data;
		distance = hit_cylinder_distance(cylinder.center, cylinder.normal, cylinder.diameter / 2,
				&ray);
		if (distance > 0.0f && distance < distance_to_light && object->data != objects_hitf)
		{
			final_color = vec3_mul(final_color, 0.05);
			break;
		}
		object = object->next;
	}
	final_color = vec3_coloraddmax(final_color, ambient_color);
	return (final_color);
}

t_vec3	calc_spheres(t_render *rd, int i, int j)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_objects	*objects;
	t_point3	pixel_center;
	t_vec3		ray_direction;
	t_ray		ray;
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
	t_list		*objects_hitf;

	camera = rd->camera;
	canvas = rd->canvas;
	objects = rd->objects;
	pixel_center = vec3_add(camera->vp->pixel_00,
			vec3_add(vec3_mul(camera->vp->pixel_du, (float)i),
				vec3_mul(camera->vp->pixel_dv, (float)j)));
	ray_direction = vec3_normalize(vec3_sub(pixel_center, camera->center));
	ray = (t_ray){.origin = camera->center, .direction = ray_direction};
	min_distance = INFINITY;
	final_color = (t_vec3){0, 0, 0};
	ambient_color = color_to_vec3(objects->ambient->color);
	ambient_color = vec3_mul(ambient_color, objects->ambient->ratio);
	object = objects->spheres;
	for (int s = 0; s < objects->sp_count; s++)
	{
		sphere = *(t_sphere *)object->data;
		distance = hit_sphere_distance(sphere.center, sphere.diameter / 2,
				&ray);
		if (distance > 0.0f && distance < min_distance)
		{
			min_distance = distance;
			hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, distance));
			normal = vec3_normalize(vec3_sub(hit_point, sphere.center));
			final_color = color_to_vec3(sphere.color);
			distance_to_light = vec3_length(vec3_sub(hit_point,
						objects->light->origin));
			light_power = objects->light->ratio / (4.0f * M_PI
					* distance_to_light * distance_to_light);
			light_color = vec3_mul(color_to_vec3(objects->light->color),
					light_power);
			light_direction = vec3_normalize(vec3_sub(objects->light->origin,
						hit_point));
			diff = fmax(vec3_dot(normal, light_direction), 0.0);
			final_color = vec3_mul(final_color, diff);
			final_color = vec3_coloradddue(final_color, light_color);
			objects_hitf = object->data;
		}
		object = object->next;
	}
	ray.origin = hit_point;
	ray.direction = light_direction;
	object = objects->spheres;
	for (int s = 0; s < objects->sp_count; s++)
	{
		sphere = *(t_sphere *)object->data;
		distance = hit_sphere_distance(sphere.center, sphere.diameter / 2,
				&ray);
		if (distance > 0.0f && distance < distance_to_light && object->data != objects_hitf)
		{
			final_color = vec3_mul(final_color, 0.05);
			break;
		}
		object = object->next;
	}
	final_color = vec3_coloradddue(final_color, ambient_color);
	return (final_color);
}

void	travelling_ray(t_render *rd, t_list *objects_hit, t_ray *ray)
{
	float		ray_length;
	t_point3	hit_point;
	t_list		*object;
	t_list		*object0;
	t_sphere	sphere;
	float		min_distance;
	t_vec3		normal;
	int s;

	ray_length = 1;
	object0 = objects_hit;
	while (ray_length > 0)
	{
		object = rd->objects->spheres;
		s = 0;
		while (s < rd->objects->sp_count)
		{
			sphere = *(t_sphere *)object->data;
			ray_length = hit_sphere_distance(sphere.center, sphere.diameter / 2,
					ray);
			if (ray_length > 0.0f && ray_length < min_distance)
			{
				min_distance = ray_length;
				hit_point = vec3_add(ray->origin, vec3_mul(ray->direction,
							ray_length));
				normal = vec3_normalize(vec3_sub(hit_point, sphere.center));
				objects_hit->next = ft_lstnew(rd->arena, object->data);
			}
			s++;

			object = object->next;
		}
		if (objects_hit)
		{
			ray->origin = hit_point;
			ray->direction = vec3_reflect(ray->direction, normal);
			objects_hit = objects_hit->next;
		}
		printf("hit: %d\n", ft_lstsize(object0));
		printf("ray_length: %f\n", ray_length);
		printf("s %d\n", s);
	}
}

void	*camera_render(void *vargp)
{
	t_render	*rd;
	t_camera	*camera;
	t_canvas	*canvas;
	t_objects	*objects;
	t_color		color;
	t_vec3		final_color;
	t_list		*objects_hit;
	t_list		*objects_hit2;
	t_ray		*ray;
	t_point3	pixel_center;

	rd = (t_render *)vargp;
	camera = rd->camera;
	canvas = rd->canvas;
	objects = rd->objects;
	int i, j;
	final_color = (t_vec3){0, 0, 0};
	for (j = 0; j < canvas->height; j++)
	{
		for (i = 0; i < canvas->width; i++)
		{
			ray = arena_temp_alloc(rd->arena, sizeof(*ray));
			objects_hit = ft_lstnew(rd->arena, NULL);
			objects_hit2 = objects_hit;
			ray->origin = camera->center;
			pixel_center = vec3_add(camera->vp->pixel_00,
					vec3_add(vec3_mul(camera->vp->pixel_du, (float)i),
						vec3_mul(camera->vp->pixel_dv, (float)j)));
			ray->direction = vec3_normalize(vec3_sub(pixel_center,
						camera->center));
			// travelling_ray(rd, objects_hit, ray);
			if (ft_lstsize(objects_hit2) > 1)
				printf("%d,", ft_lstsize(objects_hit));
			final_color = vec3_mul(calc_spheres(rd, i, j), 255);
			// final_color = vec3_mul(calc_cylinder(rd, i, j), 255);
			color = ((int)final_color.x << 16) | ((int)final_color.y << 8) | (int)final_color.z;
			canvas_draw(canvas, i, j, color);
		}
	}
	return (NULL);
}
