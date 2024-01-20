/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:07:00 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 02:19:43 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "maths/maths.h"

/* Basic camera with a viewport fixed to it.
The viewport is orthogonal to the camera direction, its center is placed where
the camera is looking at.
*/
typedef struct s_camera
{
	t_point3		center;
	t_point3		look_at;
	float			hfov;
	struct s_viewport
	{
		t_point3	pixel_00;
		t_vec3		pixel_du;
		t_vec3		pixel_dv;
	}				*vp;
}	t_camera;

t_camera	*camera_create(
	t_point3 center, t_vec3 direction, float hfov, void *arena);

void		camera_init_viewport(
	t_camera *cam, int canvas_width, int canvas_height, void *arena);


/* INTERNAL
================================================================================
*/

// Because we are limited to 5 var declarations / function
typedef struct s_vp_helper
{
	float		width;
	float		height;
	t_vec3		u;
	t_vec3		v;
	t_point3	upper_left;
}	t_vp_helper;

#endif
