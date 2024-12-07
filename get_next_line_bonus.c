/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshabali <sshabali@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:38:29 by sshabali          #+#    #+#             */
/*   Updated: 2024/12/07 23:38:30 by sshabali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char **saved)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	if (!*saved || !**saved)
		return (NULL);
	while ((*saved)[i] && (*saved)[i] != '\n')
		i++;
	line = ft_strdup(*saved);
	if ((*saved)[i] == '\n')
	{
		line[i + 1] = '\0';
		temp = ft_strdup(&(*saved)[i + 1]);
	}
	else
		temp = NULL;
	free(*saved);
	*saved = temp;
	return (line);
}

static int	read_to_buffer(int fd, char **saved)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		*saved = ft_strjoin(*saved, buffer);
	}
	free(buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*saved[MAX_FD];
	int			bytes_read;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (!saved[fd] || !ft_strchr(saved[fd], '\n'))
			bytes_read = read_to_buffer(fd, &saved[fd]);
		if (bytes_read < 0)
			break ;
		if (ft_strchr(saved[fd], '\n'))
			break ;
	}
	return (get_line(&saved[fd]));
}
