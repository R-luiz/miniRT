/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:03:08 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/02 17:03:13 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	float	res;
	float	sign;
	float	power;

	res = 0.0f;
	sign = 1.0f;
	power = 1.0f;
	if (*str == '-')
	{
		sign = -1.0f;
		str++;
	}
	while (*str && *str != '.' && *str >= '0' && *str <= '9')
	{
		res = res * 10.0f + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str && *str >= '0' && *str <= '9')
		{
			res = res * 10.0f + (*str - '0');
			power *= 10.0f;
			str++;
		}
	}
	return (sign * res / power);
}