/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:33:03 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 01:49:59 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./canvas.h"
#include "libft.h"

t_canvas	*canvas_create(int width, float aspect, void *arena)
{
	t_canvas	*c;

	c = arena_alloc(arena, sizeof(*c));
	c->width = width;
	c->height = (int)((float)width / aspect);
	c->raster = arena_alloc(arena, sizeof(*c->raster) * c->width * c->height);
	pthread_mutex_init(&c->mut, NULL);
	return (c);
}

void	canvas_destroy(t_canvas *canvas)
{
	pthread_mutex_destroy(&canvas->mut);
}

void		canvas_draw(t_canvas *canvas, int x, int y, t_color c)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y <= canvas->height)
	{
		pthread_mutex_lock(&canvas->mut);
		canvas->raster[y * canvas->width + x] = c;
		pthread_mutex_unlock(&canvas->mut);
	}
}
