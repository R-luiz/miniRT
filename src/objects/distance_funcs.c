/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:14 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/26 16:58:32 by vmalassi         ###   ########.fr       */
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

float	hit_plane_distance(t_plane *plane, t_lightray ray)
{
	float	denom;
	float	t;

	denom = vec3_dot(ray.direction, plane->normal);
	if (fabs(denom) > 0.0001)
	{
		t = vec3_dot(vec3_sub(plane->apoint, ray.origin), plane->normal)
			/ denom;
		ray.color = color_vec3(vec3_coloradddue(color_to_vec3(ray.color),
					color_to_vec3(plane->color)));
		if (t >= 0)
			return (t);
	}
	return (-1);
}
