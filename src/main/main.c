/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:35:54 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 20:57:52 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/engine.h"
#include "./options.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>

void	options_init(t_options *opt)
{
	opt->window_width = 1600;
	opt->window_aspect  = 16.f / 9;
	opt->fps = 60;
}

int	main(int argc, char *argv[])
{
	void		*arena;
	t_engine	*eng;
	t_options	options;
	int			ret = 0;

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
	engine_init(eng, &options, arena);
	engine_run(eng);
	engine_terminate(eng);
	arena_destroy(arena);
	return (ret);
}
