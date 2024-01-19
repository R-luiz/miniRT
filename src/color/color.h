/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:50:33 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 15:17:42 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "maths/maths.h"
# include <stdint.h>

typedef uint32_t	t_color;

// create color from vec3
t_color	color_vec3(t_vec3 v);
// create color from integer rgb values
t_color	color_int(uint8_t r, uint8_t g, uint8_t b);

#endif
