/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:28:35 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 22:58:25 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"

void	graphics_present(t_graphics *grph)
{
	mlx_put_image_to_window(
		grph->mlx_ptr,
		grph->win_ptr,
		grph->canvas->ptr,
		0,
		0);
}

void	graphics_clear(t_graphics *grph, t_color color)
{
	int	i;

	i = -1;
	while (++i < grph->win_height * grph->win_width)
		grph->canvas->raster[i] = color;
}
