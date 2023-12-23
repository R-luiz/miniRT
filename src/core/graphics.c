/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:22:05 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 11:29:13 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"

static int	graphics_init_mlx(t_graphics *grph)
{
	grph->mlx_ptr = mlx_init();
	if (grph->mlx_ptr == NULL)
	{
		printf("[CRITICAL] failed to initialize mlx instance\n");
		return (EXIT_FAILURE);
	}
	grph->win_ptr = mlx_new_window(
			grph->mlx_ptr,
			grph->win_width,
			grph->win_height,
			grph->win_title);
	if (grph->win_ptr == NULL)
	{
		printf("[CRITICAL] failed to create mlx window\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static t_mlx_image	*graphics_create_mlx_image(
	void *mlx_ptr, int width, int height, void *arena)
{
	t_mlx_image	*img;

	img = arena_alloc(arena, sizeof(*img));
	img->ptr = mlx_new_image(
			mlx_ptr,
			width,
			height);
	if (img->ptr == NULL)
	{
		printf("[CRITICAL] failed to create mlx image\n");
		return (NULL);
	}
	img->raster = (t_color *)mlx_get_data_addr(
			img->ptr, &img->bpp, &img->size_line, &img->endian);
	return (img);
}

static int	graphics_init_framebuffers(t_graphics *grph, void *arena)
{
	grph->front = graphics_create_mlx_image(
			grph->mlx_ptr, grph->win_width, grph->win_height, arena);
	if (grph->front == NULL)
		return (EXIT_FAILURE);
	grph->back = graphics_create_mlx_image(
			grph->mlx_ptr, grph->win_width, grph->win_height, arena);
	if (grph->back == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_graphics	*graphics_create(void *arena, int width, int height, int fps)
{
	t_graphics	*grph;

	grph = arena_alloc(arena, sizeof(*grph));
	grph->win_width = width;
	grph->win_width_half = width / 2;
	grph->win_height = height;
	grph->win_height_half = height / 2;
	grph->win_title = WINDOW_TITLE;
	grph->fps = fps;
	if (graphics_init_mlx(grph) == EXIT_FAILURE)
	{
		graphics_destroy(grph);
		return (NULL);
	}
	if (graphics_init_framebuffers(grph, arena) == EXIT_FAILURE)
	{
		graphics_destroy(grph);
		return (NULL);
	}
	return (grph);
}

void	graphics_destroy(t_graphics *grph)
{
	if (grph != NULL)
	{
		if (grph->front != NULL)
			mlx_destroy_image(grph->mlx_ptr, grph->front->ptr);
		if (grph->back != NULL)
			mlx_destroy_image(grph->mlx_ptr, grph->back->ptr);
		if (grph->win_ptr != NULL)
			mlx_destroy_window(grph->mlx_ptr, grph->win_ptr);
		if (grph->mlx_ptr != NULL)
		{
			mlx_destroy_display(grph->mlx_ptr);
			free(grph->mlx_ptr);
		}
	}
}
