/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:14 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/29 19:00:12 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

float	hit_sphere_distance(t_object *sphere, t_lightray ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(ray.origin, sphere->center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - pow(sphere->diameter / 2, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant <= 0 || a == 0)
		return (-1);
	return ((-b - sqrtf(discriminant)) / (2 * a));
}

float	hit_plane_distance(t_object *plane, t_lightray ray)
{
	float	denom;
	float	t;

	denom = vec3_dot(ray.direction, ((t_plane *)plane)->normal);
	if (fabs(denom) > 0.0001)
	{
		t = vec3_dot(vec3_sub(((t_plane *)plane)->apoint, ray.origin),
				((t_plane *)plane)->normal)
			/ denom;
		ray.color = color_vec3(vec3_coloradddue(color_to_vec3(ray.color),
					color_to_vec3(((t_plane *)plane)->color)));
		if (t >= 0)
			return (t);
	}
	return (-1);
}

float	hit_cylinder_distance(t_object *cylinder, t_lightray ray)
{
	t_cylinder	*cy;
	t_vec3		co;
	t_vec3		d;
	t_vec3		a_vec;
	t_vec3		a_perp;
	t_vec3		b_perp;
	t_plane		topcap;
	t_plane		botcap;
	t_vec3		p;
	float		denom;
	float		y0;
	float		y1;
	float		sqrt_discriminant;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t0;
	float		t1;
	float		t_cap;
	float		t_min;

	cy = (t_cylinder *)cylinder;
	co = vec3_sub(ray.origin, cy->center); // Vector from cylinder center to ray origin
	d = ray.direction; // Ray direction vector
	a_vec = vec3_normalize(cy->normal); // Cylinder axis direction

	a_perp = vec3_sub(d, vec3_mul(a_vec, vec3_dot(d, a_vec)));
	b_perp = vec3_sub(co, vec3_mul(a_vec, vec3_dot(co, a_vec)));

	// Quadratic coefficients for intersection with cylindrical surface
	a = vec3_dot(a_perp, a_perp);
	b = 2 * vec3_dot(a_perp, b_perp);
	c = vec3_dot(b_perp, b_perp) - pow(cy->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	t0 = INFINITY;
	t1 = INFINITY;
	t_cap = INFINITY;
	t_min = INFINITY;
	if (discriminant >= 0 && a != 0)
	{
		// Cylinder surface intersections
		sqrt_discriminant = sqrtf(discriminant);
		t0 = (-b - sqrt_discriminant) / (2 * a);
		t1 = (-b + sqrt_discriminant) / (2 * a);
		// Check if the intersections are within the height bounds of the cylinder
		y0 = vec3_dot(vec3_add(co, vec3_mul(d, t0)), a_vec);
		y1 = vec3_dot(vec3_add(co, vec3_mul(d, t1)), a_vec);
		if ((y0 >= 0 && y0 <= cy->height) && t0 > 0)
			t_min = fmin(t_min, t0);
		if ((y1 >= 0 && y1 <= cy->height) && t1 > 0)
			t_min = fmin(t_min, t1);
	}
	topcap.apoint = vec3_add(cy->center, vec3_mul(a_vec, cy->height));
	topcap.normal = a_vec;
	botcap.apoint = cy->center;
	botcap.normal = vec3_mul(a_vec, -1);
	denom = vec3_dot(d, topcap.normal);
	if (fabs(denom) > 0.0001)
	{
		t_cap = vec3_dot(vec3_sub(topcap.apoint, ray.origin),
				topcap.normal) / denom;
		if (t_cap >= 0)
		{
			p = vec3_add(ray.origin, vec3_mul(d, t_cap));
			if (vec3_length(vec3_sub(p, topcap.apoint)) <= cy->diameter / 2)
			{
				t_min = fmin(t_min, t_cap);
			}
		}
	}
	denom = vec3_dot(d, botcap.normal);
	if (fabs(denom) > 0.0001)
	{
		t_cap = vec3_dot(vec3_sub(botcap.apoint, ray.origin),
				botcap.normal) / denom;
		if (t_cap >= 0)
		{
			p = vec3_add(ray.origin, vec3_mul(d, t_cap));
			if (vec3_length(vec3_sub(p, botcap.apoint)) <= cy->diameter / 2)
			{
				t_min = fmin(t_min, t_cap);
			}
		}
	}
	if (t_min == INFINITY)
		return (-1);
	return (t_min);
}
