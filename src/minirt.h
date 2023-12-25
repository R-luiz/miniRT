/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:16:49 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/25 01:59:52 by liguyon          ###   ########.fr       */
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
typedef uint32_t		t_color;

typedef struct s_mlx_image
{
	void	*ptr;
	t_color	*raster;
	int		size_line;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_mlx_image;

typedef struct s_graphics
{
	int			win_width;
	int			win_height;
	double		aspect_ratio;
	char		*win_title;
	int			fps;
	void		*mlx_ptr;
	void		*win_ptr;
	t_mlx_image	*canvas;
}	t_graphics;

/*	timer
==============
*/
typedef struct s_timer
{
	long long	time_start;
}	t_timer;

/*	inputs
==============
*/
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

/*	maths
==============
*/
// 3d vector
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// another alias for t_vec3
typedef t_vec3			t_point3;

/*	ray
==============
*/
typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

/*	ray
==============
*/
// convention: right-handed coordinate system
typedef struct s_camera
{
	int			image_width;
	int			image_height;
	t_point3	center;
	t_point3	center_default;
	double		hfov;
	double		hfov_default;
	double		focal_length;
	double		vp_width;
	double		vp_height;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
	t_point3	pixel00_loc;
	bool		set;
}	t_camera;

/*	data
==============
*/
typedef struct s_data
{
	void		*arena;
	t_timer		*timer;
	t_graphics	*grph;
	t_camera	*cam;
}	t_data;

/*	functions
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
t_graphics	*graphics_create(void *arena, int width, double aspect, int fps);
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
void		render(t_graphics *grph, t_camera *view);

/*	maths
==============
*/
double		deg_to_rad(double deg);
t_vec3		vec3_add(t_vec3 v, t_vec3 w);
t_vec3		vec3_sub(t_vec3 v, t_vec3 w);
t_vec3		vec3_mul(t_vec3 v, double scalar);
t_vec3		vec3_div(t_vec3 v, double scalar);
double		vec3_length_squared(t_vec3 v);
double		vec3_length(t_vec3 v);
// returns normalized copy of v
t_vec3		vec3_unit(t_vec3 v);
// dot product = produit scalaire
double		vec3_dot(t_vec3 v, t_vec3 w);
// cross product = produit vectoriel
t_vec3		vec3_cross(t_vec3 v, t_vec3 w);

/*	colors
==============
*/
// get hex color from a vec3 color
t_color		color_from_rgb(double r, double g, double b);

/*	ray
==============
*/
// returns a position along the ray based on parameter t
t_point3	ray_at(t_ray ray, double t);

/*	view
==============
*/
t_camera	*camera_create(void *arena, int win_width, int win_height);
void		camera_init(t_camera *cam, t_point3 center, double hfov);

#endif
