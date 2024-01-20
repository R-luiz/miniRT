/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:48:18 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 01:09:04 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "color/color.h"
# include "canvas/canvas.h"

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

/* Graphics subsystem. It is basically a wrapper around mlx.
- mlx_ptr: display
- mlx_win: window
- framebuffer: the mlx_image that is put to the window
*/
typedef struct s_graphics
{
	int			win_width;
	int			win_height;
	void		*mlx_ptr;
	void		*win_ptr;
	t_mlx_image	*framebuffer;
}	t_graphics;

// Create a 'display' with the specified dimensions.
t_graphics	*graphics_create(int width, float aspect, void *arena);

// Cleanup on termination.
void		graphics_destroy(t_graphics *grph);

// Clear the framebuffer.
void		graphics_clear(t_graphics *grph);

// Copy the content of canvas to the framebuffer.
void		graphics_update_framebuffer(t_graphics *grph, t_canvas *canvas);

// Push the framebuffer to screen.
void		graphics_present(t_graphics *grph);

#endif
