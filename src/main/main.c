/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:35:54 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/01 15:26:27 by rluiz            ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	void		*arena;
	t_engine	*eng;
	t_canvas	*canvas;
	t_camera	*camera;
	t_options	options;
	t_list		*list;

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
	
	list = parsing_to_list(arena, argv[1]);
	eng = arena_alloc(arena, sizeof(*eng));
	options_init(&options);
	if (engine_init(eng, &options, arena) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
		
	canvas = canvas_create(options.window_width, options.window_aspect, arena);
	
	camera = camera_create((t_point3){0, 0, 0}, (t_vec3){0, 0, 1}, 30, arena);
	camera_init_viewport(camera, canvas->width, canvas->height, arena);
	t_render rd = (t_render){.camera = camera, .canvas = canvas, .engine = eng};
	pthread_t tid;
	pthread_create(&tid, NULL, camera_render, &rd);
	pthread_detach(tid);
	
	engine_run(eng, canvas);
	engine_terminate(eng);
	canvas_destroy(canvas);
	arena_destroy(arena);
	return (EXIT_SUCCESS);
}
