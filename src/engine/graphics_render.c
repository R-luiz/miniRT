/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:20:56 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 15:53:27 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"
#include "mlx.h"

void	graphics_present(t_graphics *grph)
{
	mlx_put_image_to_window(
		grph->mlx_ptr,
		grph->win_ptr,
		grph->framebuffer->ptr,
		0,
		0);
}

void	graphics_clear(t_graphics *grph, t_color color)
{
	int	i;

	i = -1;
	while (++i < grph->win_height * grph->win_width)
		grph->framebuffer->raster[i] = color;
}
