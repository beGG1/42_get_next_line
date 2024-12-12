/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshabali <sshabali@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:37:49 by sshabali          #+#    #+#             */
/*   Updated: 2024/12/07 23:37:52 by sshabali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*saved;
	char		*line;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (fd < 0)
		return (NULL);
	if ((saved && !ft_strchr(saved, '\n')) || !saved)
		saved = read_to_saved(fd, saved);
	if (!saved)
		return (NULL);
	line = new_line(saved);
	if (!line)
		return (ft_free(&saved));
	saved = clean_saved(saved);
	return (line);
}
