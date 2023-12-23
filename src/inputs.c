/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:44:00 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 02:38:12 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

static int	inputs_process_structure(t_data *data)
{
	mlx_loop_end(data->grph->mlx_ptr);
	return (EXIT_SUCCESS);
}

static int	inputs_process_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->grph->mlx_ptr);
	return (EXIT_SUCCESS);
}

void	inputs_bind(t_data *data)
{
	mlx_hook(data->grph->win_ptr, DestroyNotify, StructureNotifyMask,
		inputs_process_structure, data);
	mlx_hook(data->grph->win_ptr, KeyPress, KeyPressMask,
		inputs_process_keypress, data);
	// mlx_hook(data->grph->win_ptr, ButtonPress, ButtonPressMask,
	// 	inputs_process_mpress, data);
	// mlx_hook(data->grph->win_ptr, ButtonRelease, ButtonReleaseMask,
	// 	inputs_process_mrelease, data);
}
