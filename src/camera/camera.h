/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:07:00 by liguyon           #+#    #+#             */
/*   Updated: 2024/03/21 17:30:36 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "maths/maths.h"
# include "parsing/parsing.h"
# include "libft.h"
# include "objects/objects.h"

/* Basic camera with a viewport fixed to it.
The viewport is orthogonal to the camera direction, its center is placed where
the camera is looking at.
*/

typedef struct s_camera
{
	t_point3			center;
	t_point3			look_at;
	float				hfov;
	struct				s_viewport
	{
		t_point3		pixel_00;
		t_vec3			pixel_du;
		t_vec3			pixel_dv;
	} * vp;
}						t_camera;

t_camera				*camera_create(t_point3 center, t_vec3 direction,
							float hfov, void *arena);

void					camera_init_viewport(t_camera *cam, int canvas_width,
							int canvas_height, void *arena);

void					*camera_render(void *vargp);

t_camera				*find_camera(t_arena *arena, t_list *list);
/* INTERNAL
================================================================================
*/

// Because we are limited to 5 var declarations / function
typedef struct s_vp_helper
{
	float				width;
	float				height;
	t_vec3				u;
	t_vec3				v;
	t_point3			upper_left;
}						t_vp_helper;

typedef struct t_objects
{
	t_list				*spheres;
	t_list				*planes;
	t_list				*cylinders;
	t_light				*light;
	t_camera			*camera;
	t_ambient			*ambient;
	int					sp_count;
	int					pl_count;
	int					cy_count;
}						t_objects;

typedef struct s_engine	t_engine;
typedef struct s_canvas	t_canvas;
typedef struct s_render
{
	t_camera			*camera;
	t_canvas			*canvas;
	t_engine			*engine;
	t_objects			*objects;
	t_arena				*arena;
}						t_render;
t_objects				*init_objects(t_arena *arena, char *argv[]);
#endif
