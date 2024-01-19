/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:48:21 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 20:55:14 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "./graphics.h"
# include "./timer.h"
# include "main/options.h"
# include <stdbool.h>

typedef struct s_engine
{
	t_graphics	*grph;
	t_timer		*timer;
	float		timestep;
}	t_engine;

int		engine_init(t_engine *eng, t_options *opt, void *arena);
void	engine_run(t_engine *eng);
void	engine_terminate(t_engine *eng);

#endif
