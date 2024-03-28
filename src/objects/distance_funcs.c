/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:14 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/28 20:48:53 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

float	hit_sphere_distance(t_object *sphere, t_lightray ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(ray.origin, sphere->center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - pow(sphere->diameter / 2, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant <= 0 || a == 0)
		return (-1);
	return ((-b - sqrtf(discriminant)) / (2 * a));
}

float	hit_plane_distance(t_object *plane, t_lightray ray)
{
	float	denom;
	float	t;

	denom = vec3_dot(ray.direction, ((t_plane *)plane)->normal);
	if (fabs(denom) > 0.0001)
	{
		t = vec3_dot(vec3_sub(((t_plane *)plane)->apoint, ray.origin),
				((t_plane *)plane)->normal)
			/ denom;
		ray.color = color_vec3(vec3_coloradddue(color_to_vec3(ray.color),
					color_to_vec3(((t_plane *)plane)->color)));
		if (t >= 0)
			return (t);
	}
	return (-1);
}

float hit_cylinder_distance(t_object *cylinder, t_lightray ray) {
    t_cylinder *cy = (t_cylinder *)cylinder;
    t_vec3 CO = vec3_sub(ray.origin, cy->center); // Vector from cylinder center to ray origin
    t_vec3 D = ray.direction; // Ray direction vector
    t_vec3 A = vec3_normalize(cy->normal); // Cylinder axis direction

    // Compute A and B vectors perpendicular to the cylinder axis
    t_vec3 A_perp = vec3_sub(D, vec3_mul(A, vec3_dot(D, A)));
    t_vec3 B_perp = vec3_sub(CO, vec3_mul(A, vec3_dot(CO, A)));
    t_plane topcap;
    t_plane botcap;

    // Quadratic coefficients for intersection with cylindrical surface
    float a = vec3_dot(A_perp, A_perp);
    float b = 2 * vec3_dot(A_perp, B_perp);
    float c = vec3_dot(B_perp, B_perp) - pow(cy->diameter / 2, 2);
    float discriminant = b * b - 4 * a * c;
    float t0, t1, t_cap, t_min = INFINITY;
    int has_surface_intersection = 0;

    if (discriminant >= 0 && a != 0) {
        // Cylinder surface intersections
        float sqrtDiscriminant = sqrtf(discriminant);
        t0 = (-b - sqrtDiscriminant) / (2 * a);
        t1 = (-b + sqrtDiscriminant) / (2 * a);

        // Check if the intersections are within the height bounds of the cylinder
        float y0 = vec3_dot(vec3_add(CO, vec3_mul(D, t0)), A);
        float y1 = vec3_dot(vec3_add(CO, vec3_mul(D, t1)), A);

        if ((y0 >= 0 && y0 <= cy->height) && t0 > 0) {
            t_min = fmin(t_min, t0);
            has_surface_intersection = 1;
        }
        if ((y1 >= 0 && y1 <= cy->height) && t1 > 0) {
            t_min = fmin(t_min, t1);
            has_surface_intersection = 1;
        }
    }
    topcap.apoint = vec3_add(cy->center, vec3_mul(A, cy->height));
    topcap.normal = A;
    botcap.apoint = cy->center;
    botcap.normal = vec3_mul(A, -1);
    float denom = vec3_dot(D, topcap.normal);
    if (fabs(denom) > 0.0001)
    {
        t_cap = vec3_dot(vec3_sub(topcap.apoint, ray.origin), topcap.normal) / denom;
        if (t_cap >= 0)
        {
            t_vec3 P = vec3_add(ray.origin, vec3_mul(D, t_cap));
            if (vec3_length(vec3_sub(P, topcap.apoint)) <= cy->diameter / 2)
            {
                t_min = fmin(t_min, t_cap);
            }
        }
    }
    denom = vec3_dot(D, botcap.normal);
    if (fabs(denom) > 0.0001)
    {
        t_cap = vec3_dot(vec3_sub(botcap.apoint, ray.origin), botcap.normal) / denom;
        if (t_cap >= 0)
        {
            t_vec3 P = vec3_add(ray.origin, vec3_mul(D, t_cap));
            if (vec3_length(vec3_sub(P, botcap.apoint)) <= cy->diameter / 2)
            {
                t_min = fmin(t_min, t_cap);
            }
        }
    }
    if (t_min == INFINITY)
        return -1;
    return (t_min);
}
