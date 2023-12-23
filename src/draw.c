/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:52:06 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 20:14:59 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "mlx.h"

void	draw_pixel(t_graphics *grph, int x, int y, t_color c)
{
	int	sx;
	int	sy;

	sy = grph->win_height_half - y;
	sx = grph->win_width_half + x;
	if (sx >= 0 && sx < grph->win_width
		&& sy >= 0 && sy < grph->win_height)
		grph->canvas->raster[sy * grph->win_width + sx] = c;
}
