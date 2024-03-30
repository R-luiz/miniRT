/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:49:12 by liguyon           #+#    #+#             */
/*   Updated: 2024/03/30 14:08:26 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./maths.h"
#include <math.h>

float	to_rad(float deg)
{
	return ((float)(deg * M_PI / 180.0));
}

float	to_deg(float rad)
{
	return ((float)(rad * 180.0 / M_PI));
}
