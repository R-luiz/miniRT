/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:00:27 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 04:02:59 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

/* Vec3
================================================================================
*/
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

// Alias for t_vec3.
typedef t_vec3	t_point3;

t_vec3	vec3_add(t_vec3 v, t_vec3 w);
t_vec3	vec3_sub(t_vec3 v, t_vec3 w);
t_vec3	vec3_mul(t_vec3 v, float scalar);
t_vec3	vec3_div(t_vec3 v, float scalar);
float	vec3_length_squared(t_vec3 v);
float	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
float	vec3_dot(t_vec3 v, t_vec3 w);
t_vec3	vec3_cross(t_vec3 v, t_vec3 w);

/* Misc
================================================================================
*/
// Converts degrees to radians.
float	to_rad(float deg);

#endif
