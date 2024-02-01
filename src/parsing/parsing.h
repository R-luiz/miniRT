/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:28:23 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/01 16:45:26 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "camera/camera.h"
# include "libft.h"
# include "maths.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 32

struct s_list;

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

/* LIST FUNCTIONS */
t_list				*ft_lstnew(t_arena *arena, void *data);
void				ft_lstadd_back(t_list **alst, t_list *new);

/* PARSING FUNCTIONS */
t_list				*parsing_to_list(t_arena *arena, char *file);
t_list				*token_to_list(t_arena *arena, char *line);
t_camera			*find_camera(t_arena *arena, t_list *list);
#endif // !PARSING_H