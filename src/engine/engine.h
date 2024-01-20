/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:48:21 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 00:58:21 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "./graphics.h"
# include "./timer.h"
# include "main/options.h"
# include "canvas/canvas.h"
# include <stdbool.h>

/*
The engine handles:
	- the graphics subsystem (display, window, framebuffer)
	- the inputs (keyboard & structure events)
	- the timer (the timer is used for enforcing the window's FPS)
*/
typedef struct s_engine
{
	t_graphics		*grph;
	t_timer			*timer;
	float			timestep;
}	t_engine;

// Initialize the engine's subsystems with the specified options.
int		engine_init(t_engine *eng, t_options *opt, void *arena);

/* Loop the engine until the user terminates. The content of the window is
updated with the canvas every frame.*/
void	engine_run(t_engine *eng, t_canvas *canvas);

/* To be called on termination. This function performs the cleanups for all
resources that won't be released by simply destroying the arena. */
void	engine_terminate(t_engine *eng);

/* INTERNAL
================================================================================
*/
// Agregate because the callback used by mlx_loop_hook takes only one argument.
typedef struct s_loop_args
{
	t_engine	*eng;
	t_canvas	*canvas;
}	t_loop_args;

#endif
