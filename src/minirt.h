/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:16:49 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 02:39:05 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

/*	typedefs, defines, enums
================================================================================
*/

typedef uint32_t	t_color;
# define COLOR_BG 0x1A1A1A

/*	core
==============
*/
typedef struct s_mlx_image {
	void	*ptr;
	t_color	*raster;
	int		size_line;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_mlx_image;

typedef struct s_graphics {
	int			win_width;
	int			win_width_half;
	int			win_height;
	int			win_height_half;
	char		*win_title;
	int			fps;
	void		*mlx_ptr;
	void		*win_ptr;
	t_mlx_image	*front;
	t_mlx_image	*back;
}	t_graphics;

/*	timer
==============
*/
typedef struct s_timer {
	long	time_start;
}	t_timer;

/*	inputs
==============
*/
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

/*	data
==============
*/
typedef struct s_data {
	t_timer		*timer;
	t_graphics	*grph;
}	t_data;

/*
================================================================================
	functions
================================================================================
*/

/*	utils
==============
*/
// same as calloc but prints an error log when the allocation failed
void		*calloc_log(size_t nmemb, size_t size);

/*	timer
==============
*/
// Wait for the specified amout of milliseconds
void		timer_delay(int ms);
// Get time elapsed (in ms) since timer->time_start
int			timer_get_ticks(t_timer *timer);
// Timer is initialized with time at creation
t_timer		*t_timer_create(void);
void		timer_destroy(t_timer *timer);

/*	core
==============
*/
// Crate window and framebuffers using mlx
t_graphics	*graphics_create(int width, int height, char *title, int fps);
void		graphics_destroy(t_graphics *grph);
// Send back buffer to screen
void		graphics_clear(t_graphics *grph, t_color color);
void		graphics_present(t_graphics *grph);

/*	inputs
==============
*/
// register the different inputs (keyboard, mouse, structure)
void		inputs_bind(t_data *data);

/*	draw
==============
*/
// Draw pixel of color 'c' at position (x,y)
void		draw_pixel(t_graphics *grph, int x, int y, t_color c);

/*	render
==============
*/
// render pipeline
void		render(t_graphics *grph);

#endif
