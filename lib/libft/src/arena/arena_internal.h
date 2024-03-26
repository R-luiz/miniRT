/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:08:18 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/23 10:42:01 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_INTERNAL_H
# define ARENA_INTERNAL_H

# include <stdlib.h>
# include <stdint.h>

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

#endif
