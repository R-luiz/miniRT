/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 22:02:15 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/25 02:00:46 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <math.h>

void	camera_init(t_camera *cam, t_point3 center, double hfov)
{
	t_vec3		vp_u;
	t_vec3		vp_v;
	t_point3	vp_upper_left;

	if (!cam->set)
	{
		cam->center_default = center;
		cam->hfov_default = hfov;
		cam->set = true;
	}
	cam->center = center;
	cam->hfov = hfov;

	// toa
	// theta = fov / 2 ;; adjacent = focal_length
	// => oppose = tan(theta) / focal_length
	// vp_widht = 2 * oppose
	cam->vp_width = 2 * cam->focal_length * tan(deg_to_rad(hfov) / 2);
	cam->vp_height = 
		cam->vp_width * ((double)cam->image_height / cam->image_width);

	// vecteur qui va de gauche a droite du viewport
	vp_u = (t_vec3){cam->vp_width, 0, 0};

	// vecteur qui va de haut en bas du viewport
	vp_v = (t_vec3){0, -cam->vp_height, 0};

	// vecteurs dont la longueur est egale a la distance entre 2 pixels
	// sur x
	cam->pixel_delta_u = vec3_div(vp_u, cam->image_width);
	// sur y
	cam->pixel_delta_v = vec3_div(vp_v, cam->image_height);

	// position du coin haut gauche du viewport
	vp_upper_left =
		vec3_sub(cam->center, (t_vec3){0, 0, cam->focal_length});
	vp_upper_left = vec3_sub(vp_upper_left, vec3_div(vp_u, 2));
	vp_upper_left = vec3_sub(vp_upper_left, vec3_div(vp_v, 2));

	// position du tout premier pixel (x=0,y=0)
	cam->pixel00_loc = vec3_add(
		vp_upper_left, vec3_mul(
			vec3_add(cam->pixel_delta_u, cam->pixel_delta_v), 0.5));
}

t_camera	*camera_create(void *arena, int win_width, int win_height)
{
	t_camera		*cam;

	cam = arena_alloc(arena, sizeof(*cam));
	cam->image_width = win_width;
	cam->image_height = win_height;
	cam->focal_length = 1.0;
	cam->set = false;
	return (cam);
}
