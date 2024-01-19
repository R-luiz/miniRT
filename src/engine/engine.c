/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:29:10 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 17:59:49 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "mlx.h"
#include <stdlib.h>

void	inputs_bind(t_engine *eng);

int	engine_init(t_engine *eng, t_options *opt, void *arena)
{
	eng->grph = graphics_create(
		opt->window_width, opt->window_aspect, arena);
	if (!eng->grph)
		return (EXIT_FAILURE);
	eng->timer = rt_timer_create(arena);
	eng->timestep = 1e3f / opt->fps;
	inputs_bind(eng);
	return (EXIT_SUCCESS);
}

static int	main_loop(t_engine *eng)
{
	static int	last_time = 0;
	int			time_to_wait;

	time_to_wait = eng->timestep - (timer_get_ticks(eng->timer) - last_time);
	if (time_to_wait > 0 && time_to_wait <= eng->timestep)
		timer_delay(time_to_wait);
	last_time = timer_get_ticks(eng->timer);
	return (EXIT_SUCCESS);
}

void	engine_run(t_engine *eng)
{
	graphics_clear(eng->grph, 0x000000);
	// render
	graphics_present(eng->grph);
	mlx_loop_hook(eng->grph->mlx_ptr, main_loop, eng);
	mlx_loop(eng->grph->mlx_ptr);
}

void	engine_terminate(t_engine *eng)
{
	graphics_destroy(eng->grph);
}
