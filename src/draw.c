/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:52:06 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/24 22:44:44 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "mlx.h"

void	draw_pixel(t_graphics *grph, int x, int y, t_color c)
{
	if (x >= 0 && x < grph->win_width
		&& y >= 0 && y < grph->win_height)
		grph->canvas->raster[y * grph->win_width + x] = c;
}
