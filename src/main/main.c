/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:35:54 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 01:47:07 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/engine.h"
#include "canvas/canvas.h"
#include "./options.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	options_init(t_options *opt)
{
	opt->window_width = WIN_WIDTH;
	opt->window_aspect  = WIN_ASPECT;
	opt->fps = FPS;
}

int	main(int argc, char *argv[])
{
	void		*arena;
	t_engine	*eng;
	t_canvas	*canvas;
	t_options	options;

	if (argc != 2)
	{
		printf("\nusage: ./miniRT path/to/file.rt\n\n");
		return (EXIT_FAILURE);
	}
	(void)argv;
	arena = arena_init((size_t)1e8);
	if (!arena)
	{
		printf("Error: insufficient memory\n");
		return (EXIT_FAILURE);
	}
	eng = arena_alloc(arena, sizeof(*eng));
	options_init(&options);
	if (engine_init(eng, &options, arena) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	canvas = canvas_create(options.window_width, options.window_aspect, arena);
	canvas_draw(canvas, 1600/2, 900/2, 0xff0000);
	engine_run(eng, canvas);
	engine_terminate(eng);
	canvas_destroy(canvas);
	arena_destroy(arena);
	return (EXIT_SUCCESS);
}
