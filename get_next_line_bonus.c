/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahidi <azahidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:29:32 by azahidi           #+#    #+#             */
/*   Updated: 2025/12/08 14:29:35 by azahidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*ft_cleanup(char **buffer)
{
	if (*buffer != NULL)
		free(*buffer);
	*buffer = NULL;
	return (NULL);
}

static char	*ft_extract_line(char **buffer, size_t index)
{
	char	*tmp;
	char	*buffer_cpy;
	size_t	i;

	i = 0;
	buffer_cpy = *buffer;
	tmp = ft_strndup(buffer_cpy, index);
	if (!tmp)
		return (ft_cleanup(buffer));
	while (buffer_cpy[index])
		buffer_cpy[i++] = buffer_cpy[index++];
	buffer_cpy[i] = '\0';
	return (tmp);
}

static char	*ft_reallocate_buff(char **buffer, size_t occupied_size)
{
	char			*new_buffer;
	char			*old_buffer;
	size_t			i;
	unsigned long	read_buffer_size;

	read_buffer_size = (unsigned long)BUFFER_SIZE;
	i = 0;
	old_buffer = *buffer;
	new_buffer = (char *)malloc(read_buffer_size + occupied_size + 1);
	if (!new_buffer)
		return (NULL);
	while ((*buffer)[i])
	{
		new_buffer[i] = (*buffer)[i];
		i++;
	}
	new_buffer[i] = '\0';
	free(old_buffer);
	*buffer = new_buffer;
	return (new_buffer);
}

static char	*ft_read_until_newline(int fd, char **buffer, int bytes)
{
	size_t	occupied_size;
	ssize_t	newline_index;

	newline_index = ft_strchr(*buffer, '\n');
	while (newline_index == -1)
	{
		occupied_size = ft_strlen(*buffer);
		if (!ft_reallocate_buff(buffer, occupied_size))
			return (ft_cleanup(buffer));
		bytes = read(fd, *buffer + occupied_size, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_cleanup(buffer));
		(*buffer)[occupied_size + bytes] = '\0';
		if (bytes == 0)
		{
			if ((*buffer)[0] == '\0')
				return (ft_cleanup(buffer));
			return (ft_extract_line(buffer, occupied_size));
		}
		newline_index = ft_strchr(*buffer, '\n');
	}
	return (ft_extract_line(buffer, newline_index + 1));
}

char	*get_next_line(int fd)
{
	static char		*buffer[FD_BUFFER_SIZE];
	unsigned long	read_buffer_size;
	int				bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_BUFFER_SIZE)
		return (NULL);
	read_buffer_size = (unsigned long)BUFFER_SIZE;
	bytes = 0;
	if (!buffer[fd])
	{
		buffer[fd] = (char *)malloc(read_buffer_size + 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	if (!buffer[fd][0])
	{
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes == 0 || bytes == -1)
			return (ft_cleanup(&buffer[fd]));
		buffer[fd][bytes] = '\0';
	}
	return (ft_read_until_newline(fd, &buffer[fd], bytes));
}
