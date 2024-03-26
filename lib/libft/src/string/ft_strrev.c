/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liguyon <liguyon@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:03:42 by liguyon           #+#    #+#             */
/*   Updated: 2023/12/23 11:03:50 by liguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	tmp;

	if (str)
	{
		len = ft_strlen(str);
		i = -1;
		j = len - 1;
		while (++i < len / 2)
		{
			tmp = str[i];
			str[i] = str[j];
			str[j] = tmp;
			j--;
		}
	}
	return (str);
}
