/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:39:00 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 19:26:34 by liguyon          ###   ########.fr       */
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
	ret = (t_vec3){
		.x = v.x / m,
		.y = v.y / m,
		.z = v.z / m
	};
	return (ret);
}

double	vec3_dot(t_vec3 v, t_vec3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}
