/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:14 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/21 17:54:42 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

float	hit_sphere_distance(t_sphere *sphere, t_lightray *ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(ray->origin, sphere->center);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2 * vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - pow(sphere->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant <= 0)
		return (-1);
	return (-b - sqrtf(discriminant)) / (2 * a);
}

float	hit_plane_distance(t_plane *plane, t_lightray *ray)
{
	float	denom;
	float	t;

	denom = vec3_dot(plane->normal, ray->direction);
	if (fabs(denom) > 0.0001)
	{
		t = vec3_dot(vec3_sub(plane->apoint, ray->origin), plane->normal) / denom;
		if (t >= 0)
			return (t);
	}
	return (-1);
}
