/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:44:00 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 03:20:37 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./engine.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

static void	loop_end(t_engine *eng)
{
	pthread_mutex_lock(&eng->mut);
	eng->is_running = false;
	mlx_loop_end(eng->grph->mlx_ptr);
	pthread_mutex_unlock(&eng->mut);
}

static int	inputs_process_structure(t_engine *eng)
{
	loop_end(eng);
	return (0);
}

static int	inputs_process_keypress(int keycode, t_engine *eng)
{
	if (keycode == XK_Escape)
		loop_end(eng);
	return (0);
}

void	inputs_bind(t_engine *eng)
{
	mlx_hook(eng->grph->win_ptr, DestroyNotify, StructureNotifyMask,
		inputs_process_structure, eng);
	mlx_hook(eng->grph->win_ptr, KeyPress, KeyPressMask,
		inputs_process_keypress, eng);
}
