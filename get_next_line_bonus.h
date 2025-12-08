/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahidi <azahidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:30:13 by azahidi           #+#    #+#             */
/*   Updated: 2025/12/08 14:30:17 by azahidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif

# ifndef FD_BUFFER_SIZE
#  define FD_BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strndup(const char *src, size_t n);
ssize_t	ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
#endif
