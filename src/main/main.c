/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:35:54 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/22 19:17:14 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/engine.h"
#include "canvas/canvas.h"
#include "camera/camera.h"
#include "./options.h"
#include "libft.h"
#include "parsing/parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void	options_init(t_options *opt)
{
	opt->window_width = WIN_WIDTH;
	opt->window_aspect  = WIN_ASPECT;
	opt->fps = FPS;
}

void	exit_error(char *msg)
{
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	void		*arena;
	t_engine	*eng;
	t_canvas	*canvas;
	t_objects	*objects;
	t_options	options;

	if (argc != 2)
		exit_error("\nusage: ./miniRT path/to/file.rt\n\n");
	arena = arena_init((size_t)1e10);
	if (!arena)
		exit_error("Error: insufficient memory\n");
	eng = arena_alloc(arena, sizeof(*eng));
	options_init(&options);
	objects = init_objects(arena, argv);
	canvas = canvas_create(options.window_width, options.window_aspect, arena);
	t_render rd = (t_render){.camera = objects->camera, .canvas = canvas, .engine = eng, .objects = objects, .arena = arena};
	if (engine_init(&rd, &options, arena) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	camera_init_viewport(objects->camera, canvas->width, canvas->height, arena);
	camera_render(&rd);
	engine_run(&rd, canvas, objects->camera);
	engine_terminate(eng);
	canvas_destroy(canvas);
	arena_destroy(arena);
	return (EXIT_SUCCESS);
}
