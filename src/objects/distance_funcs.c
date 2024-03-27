/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:14 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/27 17:12:38 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

float	hit_sphere_distance(void *sphere, t_lightray ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(ray.origin, ((t_sphere *)sphere)->center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - pow(((t_sphere *)sphere)->diameter / 2, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant <= 0 || a == 0)
		return (-1);
	return ((-b - sqrtf(discriminant)) / (2 * a));
}

float	hit_plane_distance(void *plane, t_lightray ray)
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

// float	hit_cylinder_distance(void *cylinder, t_lightray ray)
// {
// 	t_vec3	oc;
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	discriminant;

// 	oc = vec3_sub(ray.origin, ((t_cylinder *)cylinder)->center);
// 	a = vec3_dot(ray.direction, ray.direction)
// 		- pow(vec3_dot(ray.direction, ((t_cylinder *)cylinder)->normal), 2);
// 	b = 2 * (vec3_dot(oc, ray.direction)
// 			- vec3_dot(ray.direction, ((t_cylinder *)cylinder)->normal)
// 			* vec3_dot(oc, ((t_cylinder *)cylinder)->normal));
// 	c = vec3_dot(oc, oc)
// 		- pow(vec3_dot(oc, ((t_cylinder *)cylinder)->normal), 2)
// 		- pow(((t_cylinder *)cylinder)->diameter / 2, 2);
// 	discriminant = pow(b, 2) - 4 * a * c;
// 	if (discriminant <= 0 || a == 0)
// 		return (-1);
// 	return ((-b - sqrtf(discriminant)) / (2 * a));
// }
