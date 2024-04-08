/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:18:42 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/08 15:04:30 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	basic_check(char *str, int i, int *comma, int *dot)
{
	if (str[i] == ',')
		*(comma) += 1;
	if (str[i] == '.')
		*(dot) += 1;
	if (str[i] == ',' && str[i + 1] && str[i + 1] == ',')
		return (0);
	if (str[i] == '.' && str[i + 1] && str[i + 1] == '.')
		return (0);
	if (str[i] == '.' && str[i + 1] && str[i + 1] == ',')
		return (0);
	if (str[i] == ',' && str[i + 1] && str[i + 1] == '.')
		return (0);
	return (1);
}

int	is_coordinates(char *str)
{
	int	i;
	int	comma;
	int	dot;

	i = 0;
	comma = 0;
	dot = 0;
	if (str[0] == '.' || str[0] == ',')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		if (!basic_check(str, i, &comma, &dot))
			return (0);
		if (dot > 3 || comma > 2 || (str[i] != ',' && str[i] != '-'
				&& str[i] != '.' && (str[i] < '0' || str[i] > '9')))
			return (0);
		if (i > 0 && str[i - 1] != ' ' && str[i] == '-' && str[i - 1] != ',')
			return (0);
		i++;
	}
	if (comma != 2 || dot > 3 || (i > 0 && str[i - 1] == ','))
		return (0);
	return (1);
}

float	safe_atof(t_arena *arena, char *str)
{
	if (!str)
		free_and_exit_error(arena, "Invalid input");
	return (ft_atof(str));
}

int	safe_atoi(t_arena *arena, const char *nptr)
{
	if (!nptr)
		free_and_exit_error(arena, "Invalid input");
	return (ft_atoi(nptr));
}

t_list	*find_id_line(t_list *list, char *id)
{
	t_list	*tmp;

	tmp = list->next;
	while (tmp)
	{
		if (ft_strcmp(((t_list *)tmp->data)->data, id) == 0)
		{
			tmp = tmp->data;
			break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}
