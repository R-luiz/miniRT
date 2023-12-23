/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:24:18 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 14:39:36 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_vec3	vec3_add(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){
		.x = v.x + w.x,
		.y = v.y + w.y,
		.z = v.z + w.z
	};
	return (ret);
}

t_vec3	vec3_sub(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){
		.x = v.x - w.x,
		.y = v.y - w.y,
		.z = v.z - w.z
	};
	return (ret);
}

t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	t_vec3	ret;

	ret = (t_vec3){
		.x = v.x * scalar,
		.y = v.y * scalar,
		.z = v.z * scalar
	};
	return (ret);
}

double	vec3_magnitude(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_unit(t_vec3 v)
{
	t_vec3	ret;
	double	m;

	m = vec3_magnitude(v);
	ret = (t_vec3){
		.x = v.x / m,
		.y = v.y / m,
		.z = v.z / m
	};
	return (ret);
}
