/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:16:49 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 11:27:09 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

/*	typedefs, defines, enums
================================================================================
*/

/*	config
==============
*/
# define SIZE_ARENA 1e8
# define WINDOW_TITLE "miniRT"
# define COLOR_BG 0x1A1A1A

/*	core
==============
*/
typedef uint32_t	t_color;

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
	void		*arena;
	t_timer		*timer;
	t_graphics	*grph;
}	t_data;

/*
================================================================================
	functions
================================================================================
*/

/*	timer
==============
*/
// Sleep for the specified number of milliseconds
void		timer_delay(int ms);
// get time (in ms) elapsed since creation of timer
int			timer_get_ticks(t_timer *timer);
// Timer is initialized with time at creation
t_timer		*timer_init(void *arena);

/*	core
==============
*/
// Crate mlx window and framebuffers
t_graphics	*graphics_create(void *arena, int width, int height, int fps);
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
