/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:22:08 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/23 01:19:42 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*arena_init(size_t buffer_size)
{
	t_arena	*a;
	void	*buf;

	buf = malloc(buffer_size);
	if (!buf)
		return (NULL);
	a = malloc(sizeof(t_arena));
	if (!a)
		return (NULL);
	a->buf = buf;
	a->buf_size = buffer_size;
	a->curr_offset = 0;
	a->prev_offset = 0;
	a->tempo_offset = 0;
	return (a);
}

void	arena_reset(t_arena *a)
{
	a->curr_offset = 0;
	a->prev_offset = 0;
	a->tempo_offset = 0;
}

void	*arena_temp_alloc(t_arena *a, size_t size)
{
	uintptr_t	curr_temp_ptr;
	void		*ptr;

	curr_temp_ptr = (uintptr_t)a->buf + (uintptr_t)a->buf_size
		- (uintptr_t)a->tempo_offset - (uintptr_t)size;
	if (curr_temp_ptr <= (uintptr_t)a->buf + (uintptr_t)a->curr_offset)
		return (NULL);
	ptr = (unsigned char *)curr_temp_ptr;
	a->tempo_offset = a->tempo_offset + size;
	return (ptr);
}

void	arena_destroy(t_arena *a)
{
	arena_reset(a);
	if (a->buf)
		free(a->buf);
	free(a);
}

void	arena_memset_temp(t_arena *a)
{
	arena_memset(a->buf + (uintptr_t)a->buf_size - (uintptr_t)a->tempo_offset, 0, a->tempo_offset);
	a->tempo_offset = 0;
}
