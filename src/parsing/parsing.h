/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:28:23 by rluiz             #+#    #+#             */
/*   Updated: 2024/02/02 17:47:00 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "camera/camera.h"
# include "color/color.h"
# include "libft.h"
# include "maths/maths.h"
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

typedef struct s_ambient
{
	float			ratio;
	t_color			color;
}					t_ambient;

typedef struct s_light
{
	t_point3		origin;
	float			ratio;
	t_color			color;
}					t_light;

typedef struct s_sphere
{
	t_point3		center;
	float			diameter;
	t_color			color;
}					t_sphere;

typedef struct s_plane
{
	t_point3		apoint;
	t_vec3			normal;
	t_color			color;
}					t_plane;

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
t_ambient			*find_ambient(t_arena *arena, t_list *list);
t_light				*find_light(t_arena *arena, t_list *list);
t_list				*find_spheres(t_arena *arena, t_list *list_params);
t_list				*find_planes(t_arena *arena, t_list *list_params);
#endif // !PARSING_H