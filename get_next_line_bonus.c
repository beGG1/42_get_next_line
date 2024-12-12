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

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_saved(char *saved)
{
	char	*temp;
	char	*ptr_end;
	int		len;

	ptr_end = ft_strchr(saved, '\n');
	if (!ptr_end)
		return (ft_free(&saved));
	else
		len = (ptr_end - saved) + 1;
	if (!saved[len])
		return (ft_free(&saved));
	temp = ft_substr(saved, len, ft_strlen(saved) - len);
	ft_free(&saved);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*new_line(char *saved)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(saved, '\n');
	len = (ptr - saved) + 1;
	line = ft_substr(saved, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_to_saved(int fd, char *saved)
{
	int		read_bytes;
	char	*buffer;

	read_bytes = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(&saved));
	buffer[0] = '\0';
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buffer[read_bytes] = '\0';
			saved = ft_strjoin(saved, buffer);
		}
	}
	free(buffer);
	if (read_bytes == -1)
		return (ft_free(&saved));
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved[MAX_FD];
	char		*line;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (fd < 0)
		return (NULL);
	if ((saved[fd] && !ft_strchr(saved[fd], '\n')) || !saved[fd])
		saved[fd] = read_to_saved(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = new_line(saved[fd]);
	if (!line)
		return (ft_free(&saved[fd]));
	saved[fd] = clean_saved(saved[fd]);
	return (line);
}
