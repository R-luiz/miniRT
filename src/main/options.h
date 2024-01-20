/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:51:11 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/20 00:28:55 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# define WIN_WIDTH	1600
# define WIN_ASPECT	16.f / 9
# define FPS 10

typedef struct s_options
{
	int		window_width;
	float	window_aspect;
	float	fps;
}	t_options;

#endif
