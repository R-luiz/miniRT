/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:39:00 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/25 05:11:07 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_unit(t_vec3 v)
{
	t_vec3	ret;
	double	m;

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

t_vec3	vec3_cross(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){
		.x = v.y * w.z - v.z * w.y,
		.y = v.z * w.x - v.x * w.z,
		.z = v.x * w.y - v.y * w.x
	};
	return (ret);
}

t_vec3	vec3_div(t_vec3 v, double scalar)
{
	t_vec3	ret;

	ret = (t_vec3){
		.x = v.x / scalar,
		.y = v.y / scalar,
		.z = v.z / scalar
	};
	return (ret);
}
