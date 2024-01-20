/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:25:30 by liguyon           #+#    #+#             */
/*   Updated: 2024/01/19 17:59:49 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

typedef struct s_timer
{
	long long	time_start;
}	t_timer;

// Timer is initialized with time at creation
t_timer	*rt_timer_create(void *arena);

// Sleep for the specified number of milliseconds
void	timer_delay(int ms);

// get time (in ms) elapsed since creation of timer
int		timer_get_ticks(t_timer *timer);

#endif
