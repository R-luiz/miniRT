/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:36:48 by liguyon           #+#    #+#             */
/*   Updated: 2024/02/01 14:59:51 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdint.h>
# include "arena_internal.h"

/*	c lib
==============
*/
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isspace(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strdup(const char *s);
char		*ft_itoa(int n);
void		*ft_realloc(void *ptr, size_t size);
char		*ft_strrev(char *str);

/*	arena allocator
==============
*/
void		*arena_init(size_t buffer_size);
void		arena_reset(void *arena);
void		*arena_alloc(void *arena, size_t size);
void		arena_destroy(void *arena);
void		arena_memset_temp(void *arena);

#endif
