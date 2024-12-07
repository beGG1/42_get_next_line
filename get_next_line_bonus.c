#include "get_next_line.h"	

static char	*read_line(int fd, char *buffer, char *str)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line != 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		if (!str)
			str = ft_calloc(1, 1);
		temp = str;
		str = ft_strjoin(str, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n') > 0)
			break ;
	}
	return (str);
}

static char	*extract(char *line)
{
	size_t	end;
	char	*str;

	end = 0;
	while (line[end] != '\n' && line[end] != '\0')
		end++;
	if (line[end] == '\0')
		return (0);
	str = ft_substr(line, end + 1, ft_strlen(line) - end);
	if (!str || *str == 0)
		return (NULL);
	line[end + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_calloc(1,BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	line = read_line(fd, buffer, str[fd]);
	free(buffer);
	if (!line)
		return (NULL);
	str[fd] = extract(line);
	return (line);
}