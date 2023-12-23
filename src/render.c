/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:34:02 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 02:55:02 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_graphics *grph)
{
	draw_pixel(grph, 0, 0, 0xff0000);
	draw_pixel(grph, -800, 450, 0xff0000);
	draw_pixel(grph, -800, -449, 0xff0000);
	draw_pixel(grph, 799, -449, 0xff0000);
	draw_pixel(grph, 799, 450, 0xff0000);
}
