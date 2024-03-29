/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:18:42 by vmalassi          #+#    #+#             */
/*   Updated: 2024/03/29 08:08:19 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_coordinates(char *str)
{
	int	i;
	int	comma;
	int dot;

	i = 0;
	comma = 0;
	dot = 0;
	while (str[i])
	{
		if(str[i] == '\n')
			break ;
		if (str[i] == ',')
			comma++;
		if (str[i] == '.')
			dot++;
		if (dot > 1 || comma > 2 || (str[i] != ',' && str[i] != '-' && str[i] != '.' && (str[i] < '0' || str[i] > '9')))
			return (0);
		if (str[i] == '-' && str[i - 1] != ',' && (i != 0 && str[i - 1]!= ' '))
			return (0);
		i++;
	}
	if(comma != 2 || dot > 1 || str[i] == ',' || ((str[i] < '0' || str[i] > '9') && str[i - 1] == ','))
		return (0);
	return (1);
}