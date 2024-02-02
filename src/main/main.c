/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:35:54 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/02 17:48:40 by rluiz            ###   ########.fr       */
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
	t_ambient	*ambient;
	t_light		*light;
	t_list		*spheres;
	t_list		*planes;
	t_options	options;
	t_list		*params;

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
	params = parsing_to_list(arena, argv[1]);
	eng = arena_alloc(arena, sizeof(*eng));
	options_init(&options);
	if (engine_init(eng, &options, arena) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	canvas = canvas_create(options.window_width, options.window_aspect, arena);
	camera = find_camera(arena, params);
	ambient = find_ambient(arena, params);
	light = find_light(arena, params);
	spheres = find_spheres(arena, params);
	planes = find_planes(arena, params);
	printf("camera: %f %f %f\n", camera->look_at.x, camera->look_at.y, camera->look_at.z);
	printf("ambient: %f\n", ambient->ratio);
	printf("light: %f %f %f\n", light->origin.x, light->origin.y, light->origin.z);
	printf("sphere1: %f %f %f\n", ((t_sphere *)spheres->data)->center.x, ((t_sphere *)spheres->data)->center.y, ((t_sphere *)spheres->data)->center.z);
	printf("sphere2: %f %f %f\n", ((t_sphere *)spheres->next->data)->center.x, ((t_sphere *)spheres->next->data)->center.y, ((t_sphere *)spheres->next->data)->center.z);
	printf("plane1: %f %f %f\n", ((t_plane *)planes->data)->apoint.x, ((t_plane *)planes->data)->apoint.y, ((t_plane *)planes->data)->apoint.z);
	printf("plane1 normal: %f %f %f\n", ((t_plane *)planes->data)->normal.x, ((t_plane *)planes->data)->normal.y, ((t_plane *)planes->data)->normal.z);
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
