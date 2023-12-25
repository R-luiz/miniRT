/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:42:40 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/25 05:27:54 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"

/* main loop:
	1) enfore fixed timestep (fps)
	3) update
	2) clear back buffer
	3) render pipeline
	4) push to screen
*/
static int	main_loop(t_data *data)
{
	static int	last_time = 0;
#ifndef PROFILE
	int			time_to_wait;

	time_to_wait = 1e3 / data->grph->fps
		- (timer_get_ticks(data->timer) - last_time);
	if (time_to_wait > 0 && time_to_wait <= 1e3 / data->grph->fps)
		timer_delay(time_to_wait);

#else
	static int iter = 0;
	
	#ifdef PROFILE_FPS
		// measure max achievable fps
		static int elapsed = 0;
		elapsed += timer_get_ticks(data->timer) - last_time;
		if (elapsed >= 1000)
		{
			printf("fps: %d\n", iter);
			elapsed -= 1000;
			iter = 0;
		}
	#else
		#define TARGET_ITER 25
		// for profiling the program with a fixed number of iterations
		if (iter > TARGET_ITER)
			mlx_loop_end(data->grph->mlx_ptr);
	#endif

	++iter;
#endif
	last_time = timer_get_ticks(data->timer);
	// update(data);

	graphics_clear(data->grph, COLOR_BG);
	render(data->grph, data->cam);
	
	// Necessary if text is drawn on screen
	// mlx_clear_window(data->grph->mlx_ptr, data->grph->win_ptr);
	
	graphics_present(data->grph);

	return (EXIT_SUCCESS);
}

static int	run(t_data *data, const char *filename)
{
	data->grph = graphics_create(data->arena, 1600, (16.0 / 9.0), 60);
	if (!data->grph)
		return (EXIT_FAILURE);
	data->timer = timer_init(data->arena);
	data->cam = camera_create(
		data->arena, data->grph->win_width, data->grph->win_height);
	// when parsing is implemented
	// initialize camera with data parsed from file.rt
	camera_init(data->cam, (t_point3){0, 0, 1}, 60);
	inputs_bind(data);
	(void)filename;
	mlx_loop_hook(data->grph->mlx_ptr, main_loop, data);
	printf("[INFO] miniRT initialized successfully\n");
	mlx_loop(data->grph->mlx_ptr);
	return (EXIT_SUCCESS);
}

static void	terminate(t_data *data)
{
	graphics_destroy(data->grph);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	void	*arena;
	int		ret;

	if (argc != 2)
	{
		printf("\nusage: ./miniRT path/to/file.rt\n\n");
		return (EXIT_FAILURE);
	}
	ret = EXIT_FAILURE;
	arena = arena_init(SIZE_ARENA);
	if (!arena)
	{
		printf("[CRITICAL] insufficient memory\n");
		return (EXIT_FAILURE);
	}
	data = arena_alloc(arena, sizeof(*data));
	data->arena = arena;
	ret = run(data, argv[1]);
	terminate(data);
	arena_destroy(arena);
	printf("[INFO] miniRT terminated successfully\n");
	return (ret);
}
