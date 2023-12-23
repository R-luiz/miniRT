/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:28:35 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 02:55:28 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"

void	graphics_present(t_graphics *grph)
{
	void		*tmp;

	tmp = grph->front;
	grph->front = grph->back;
	grph->back = tmp;
	mlx_put_image_to_window(
		grph->mlx_ptr,
		grph->win_ptr,
		grph->front->ptr,
		0,
		0);
}

void	graphics_clear(t_graphics *grph, t_color color)
{
	ft_memset(grph->back->raster, (int)color,
		sizeof(color) * grph->win_width * grph->win_height);
}
