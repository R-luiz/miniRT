/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:24:18 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/22 19:02:47 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./maths.h"

t_vec3	vec3_add(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.x + w.x, .y = v.y + w.y, .z = v.z + w.z};
	return (ret);
}

t_vec3	vec3_sub(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.x - w.x, .y = v.y - w.y, .z = v.z - w.z};
	return (ret);
}

t_vec3	vec3_mul(t_vec3 v, float scalar)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar};
	return (ret);
}

t_vec3	vec3_div(t_vec3 v, float scalar)
{
	t_vec3	ret;

	ret = (t_vec3){.x = v.x / scalar, .y = v.y / scalar, .z = v.z / scalar};
	return (ret);
}

float	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vec3_mean(t_vec3 v, t_vec3 w)
{
	t_vec3	ret;

	ret = (t_vec3){.x = (v.x + w.x) / 2, .y = (v.y + w.y) / 2, .z = (v.z + w.z)
		/ 2};
	return (ret);
}

t_vec3	vec3_coloradddue(t_vec3 color1, t_vec3 color2)
{
	t_vec3	result;
	float	maxComponentValue;

	result = vec3_add(color1, color2);
	maxComponentValue = fmax(result.x, fmax(result.y, result.z));
	if (maxComponentValue > 1.0f)
	{
		result.x /= maxComponentValue;
		result.y /= maxComponentValue;
		result.z /= maxComponentValue;
	}
	return (result);
}

t_vec3	vec3_coloraddmax(t_vec3 color1, t_vec3 color2)
{
	t_vec3	result;

	result = vec3_add(color1, color2);
	if (result.x > 1.0f)
		result.x = 1.0f;
	if (result.y > 1.0f)
		result.y = 1.0f;
	if (result.z > 1.0f)
		result.z = 1.0f;
	return (result);
}

