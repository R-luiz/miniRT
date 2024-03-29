/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:23 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/27 17:46:50 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "color/color.h"
# include "libft.h"
# include "maths/maths.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_lightray
{
	t_point3	origin;
	t_vec3		direction;
	t_color		color;
}				t_lightray;

typedef struct s_sphere
{
	t_point3	center;
	float		diameter;
	t_color		color;
	t_lightray	(*bounce)(void *obj, t_lightray ray);
	float		(*hit_dist)(void *obj, t_lightray ray);
}				t_sphere;

typedef struct s_plane
{
	t_point3	apoint;
	t_vec3		normal;
	t_color		color;
	t_lightray	(*bounce)(void *obj, t_lightray ray);
	float		(*hit_dist)(void *obj, t_lightray ray);
}				t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		normal;
	float		diameter;
	float		height;
	t_color		color;
	t_lightray	(*bounce)(void *obj, t_lightray ray);
	float		(*hit_dist)(void *obj, t_lightray ray);
}				t_cylinder;

float	hit_sphere_distance(void *sphere, t_lightray ray);
float	hit_plane_distance(void *plane, t_lightray ray);
float	hit_cylinder_distance(void *cylinder, t_lightray ray);

#endif // !OBJECTS_H