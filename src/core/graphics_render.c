/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:28:35 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 20:15:11 by liguyon          ###   ########.fr       */
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
	ft_memset(grph->canvas->raster, (int)color,
		sizeof(color) * grph->win_width * grph->win_height);
}
