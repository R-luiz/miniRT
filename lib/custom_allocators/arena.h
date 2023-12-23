/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:08:18 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/23 00:58:02 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_arena
{
	void	*buf;
	size_t	buf_size;
	size_t	prev_offset;
	size_t	curr_offset;
	size_t	tempo_offset;
}			t_arena;

void		*arena_memset(void *s, int c, size_t n);
void		*arena_temp_alloc(t_arena *a, size_t size);
void		*arena_alloc(t_arena *a, size_t size);
void		*arena_init(size_t buffer_size);
void		arena_destroy(t_arena *a);
void		arena_memset_temp(t_arena *a);