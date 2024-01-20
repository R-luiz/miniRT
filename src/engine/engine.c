/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:29:10 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 01:22:44 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "maths/maths.h"
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

static int	main_loop(t_loop_args *args)
{
	t_engine	*eng;
	t_canvas	*canvas;
	static int	last_time = 0;
	int			time_to_wait;

	eng = args->eng;
	canvas = args->canvas;
	time_to_wait = eng->timestep - (timer_get_ticks(eng->timer) - last_time);
	if (time_to_wait > 0 && time_to_wait <= eng->timestep)
		timer_delay(time_to_wait);
	last_time = timer_get_ticks(eng->timer);
	graphics_clear(eng->grph);
	graphics_update_framebuffer(eng->grph, canvas);
	graphics_present(eng->grph);
	return (EXIT_SUCCESS);
}

void	engine_run(t_engine *eng, t_canvas *canvas)
{
	t_loop_args	args;

	args.eng = eng;
	args.canvas = canvas;
	mlx_loop_hook(eng->grph->mlx_ptr, main_loop, &args);
	mlx_loop(eng->grph->mlx_ptr);
}

void	engine_terminate(t_engine *eng)
{
	graphics_destroy(eng->grph);
}
