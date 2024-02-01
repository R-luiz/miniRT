/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:28:23 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/01 14:59:56 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 32

typedef struct		s_list;

typedef struct s_list
{
	void			*data;
	struct s_list	*next;

}					t_list;

/* GET NEXT LINE FUNCTIONS */
int					ft_check_line(char *dest);
int					ft_strlen_line(char *dest);
char				*ft_join_line(char *src, char *buff);
void				ft_cute_line(char *dest);
char				*get_next_line(int fd);

#endif // !PARSING_H