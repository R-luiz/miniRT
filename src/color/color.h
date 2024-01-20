/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:50:33 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 01:29:58 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "maths/maths.h"
# include <stdint.h>

/* A8R8G8B8 color.
Alpha channel is always defaulted to 0 (opaque with minilibx-linux).*/
typedef uint32_t	t_color;

/* Create color from a vector.
Each channel is expressed as a float in range [0.f, 1.f]. */
t_color	color_vec3(t_vec3 v);

/* Create color from integer rgb values.
Each channel is expressed as an integer in ranger [0, 255]. */
t_color	color_int(uint8_t r, uint8_t g, uint8_t b);

#endif
