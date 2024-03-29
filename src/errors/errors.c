/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:07:19 by vmalassi          #+#    #+#             */
/*   Updated: 2024/03/29 11:02:18 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	exit_error(char *msg)
{
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	free_and_exit_error(t_arena *arena, char *msg)
{
	arena_destroy(arena);
	exit_error(msg);
}
