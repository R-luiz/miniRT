/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:48:18 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 16:17:22 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "color/color.h"

typedef struct s_mlx_image
{
	void			*ptr;
	t_color			*raster;
	int				size_line;
	int				bpp;
	int				endian;
	int				width;
	int				height;
}	t_mlx_image;

typedef struct s_graphics
{
	int			win_width;
	int			win_height;
	int			fps;
	void		*mlx_ptr;
	void		*win_ptr;
	t_mlx_image	*framebuffer;
}	t_graphics;

t_graphics	*graphics_create(int width, float aspect, void *arena);
void		graphics_destroy(t_graphics *grph);
void		graphics_clear(t_graphics *grph, t_color color);
void		graphics_present(t_graphics *grph);

#endif
