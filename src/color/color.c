/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:50:15 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 17:57:44 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

static float clamp_f(float x, float min, float max)
{
	if (x < min)
		return (min);
	else if (x > max)
		return (max);
	else
		return (x);
}

t_color	color_vec3(t_vec3 v)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (uint8_t)(clamp_f(v.x, 0, 255) * 255.f);
	g = (uint8_t)(clamp_f(v.y, 0, 255) * 255.f);
	b = (uint8_t)(clamp_f(v.z, 0, 255) * 255.f);
	return (r << 16 | g << 8 | b);
}

t_color	color_int(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}
