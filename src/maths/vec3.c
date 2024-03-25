/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:24:18 by liguyon           #+#    #+#             */
/*   Updated: 2024/03/25 17:56:58 by rluiz            ###   ########.fr       */
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

	if (color1.x == 0 || color2.x == 0)
		result.x = 0;
	else
		result.x = fmaxf(color1.x, color2.x);
	if (color1.y == 0 || color2.y == 0)
		result.y = 0;
	else
		result.y = fmaxf(color1.y, color2.y);
	if (color1.z == 0 || color2.z == 0)
		result.z = 0;
	else
		result.z = fmaxf(color1.z, color2.z);
	return (result);
}

t_vec3	vec3_coloradddueamb(t_vec3 color1, t_vec3 color2)
{
	t_vec3	result;

	if (color1.x == 0 || color2.x == 0)
		result.x = 0;
	else
		result.x = fmax(color1.x/2 + color2.x/2, 0.99999f);
	if (color1.y == 0 || color2.y == 0)
		result.y = 0;
	else
		result.y = fmax(color1.y /2+ color2.y/2, 0.99999f);
	if (color1.z == 0 || color2.z == 0)
		result.z = 0;
	else
		result.z = fmax(color1.z /2+ color2.z/2, 0.99999f);
	return (result);
}

t_vec3	vec3_coloraddmax(t_vec3 color1, t_vec3 color2)
{
	t_vec3	result;

	result = vec3_add(color1, color2);
	if (result.x > 0.99999999f)
		result.x = 0.99999999f;
	if (result.y > 0.99999999f)
		result.y = 0.99999999f;
	if (result.z > 0.99999999f)
		result.z = 0.99999999f;
	return (result);
}
