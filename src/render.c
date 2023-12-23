/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:34:02 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 15:11:11 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_graphics *grph)
{
	t_color	c;

	draw_pixel(grph, 0, 0, 0xff0000);
	draw_pixel(grph, -800, 450, 0xff0000);
	draw_pixel(grph, -800, -449, 0xff0000);
	draw_pixel(grph, 799, -449, 0xff0000);
	draw_pixel(grph, 799, 450, 0xff0000);
	c = color_from_rgb((t_vec3){0.9, 0.0, 0.9});
	draw_pixel(grph, 10, 10, c);
}
