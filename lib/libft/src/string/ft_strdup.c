/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 00:45:28 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/01 15:35:31 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(t_arena *arena, const char *s)
{
	char	*res;
	size_t	i;

	res = arena_alloc(arena, sizeof(char) * (1 + ft_strlen(s)));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
