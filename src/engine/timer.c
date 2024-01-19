/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:54:30 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 17:59:49 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./timer.h"
#include "libft.h"
#include <time.h>

void	timer_delay(int ms)
{
	struct timespec	ts;

	if (ms > 0)
	{
		ts.tv_sec = ms / 1e3;
		ts.tv_nsec = (ms % (int)1e3) * 1e6;
	}
	nanosleep(&ts, &ts);
}

int	timer_get_ticks(t_timer *timer)
{
	struct timespec	now;
	int				now_ms;

	clock_gettime(CLOCK_MONOTONIC, &now);
	now_ms = now.tv_sec * 1e3 + now.tv_nsec / 1e6;
	return (now_ms - timer->time_start);
}

t_timer	*rt_timer_create(void *arena)
{
	t_timer			*timer;
	struct timespec	now;

	timer = arena_alloc(arena, sizeof(*timer));
	clock_gettime(CLOCK_MONOTONIC, &now);
	timer->time_start = now.tv_sec * 1e3 + now.tv_nsec / 1e6;
	return (timer);
}
