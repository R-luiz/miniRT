/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:14 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/21 17:08:45 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

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
