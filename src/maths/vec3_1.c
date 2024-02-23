/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:39:00 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/23 15:06:28 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./maths.h"
#include <math.h>

float	vec3_length(t_vec3 v)
{
	return ((float)sqrt(vec3_length_squared(v)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	t_vec3	ret;
	float	m;

	m = vec3_length(v);
	ret = (t_vec3){.x = v.x / m, .y = v.y / m, .z = v.z / m};
	return (ret);
}

float	vec3_dot(t_vec3 v, t_vec3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_vec3	vec3_cross(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.y * w.z - v.z * w.y, .y = v.z * w.x - v.x * w.z,
		.z = v.x * w.y - v.y * w.x};
	return (ret);
}

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	float	dot;
	t_vec3	reflected;

	dot = vec3_dot(v, n);
	reflected = vec3_sub(v, vec3_mul(n, 2 * dot));
	return (reflected);
}
