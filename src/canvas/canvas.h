/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:14:51 by liguyon           #+#    #+#             */
/*   Updated: 2024/03/26 08:37:12 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "color/color.h"
# include "main/options.h"

/* The canvas on which all drawing is done.
Read and write operations are performed asynchronously: the main thread reads
the canvas to update the image on screen while the thread responsible for
rendering updates the canvas. */
typedef struct s_canvas
{
	int				width;
	int				height;
	t_color			*raster;
}	t_canvas;

// Create a canvas with the specified dimensions.
t_canvas	*canvas_create(int width, float aspect, void *arena);

// Cleanup.
void		canvas_destroy(t_canvas *canvas);

// Draw a pixel on the canvas.
void		canvas_draw(t_canvas *canvas, int x, int y, t_color c);

#endif
