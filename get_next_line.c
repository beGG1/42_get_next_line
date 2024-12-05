#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	char		*s;
	size_t		i;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (dest < src)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			d[n - 1 - i] = s[n - 1 - i];
			i++;
		}
	}
	return (dest);
}

char	*get_line(int fd, char	*buf)
{
	char	*out;
	int		n_bits;
	int		n_l;

	out = ft_calloc(1, 1);
	if (buf[0] == 0)
		n_bits = read(fd, buf, BUFFER_SIZE);
	else
	{
		n_l = ft_strchr(buf, '\n');
		if (n_l > 0)
		{
			out = ft_strjoin(out, ft_substr(buf, 0, n_l));
			ft_memmove(buf, buf + n_l, BUFFER_SIZE - n_l);
			return (out);
		}

	}
	if (n_bits <= 0)
		return (NULL);
	return (out);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	line = get_line(fd, buffer);
	return (line);
}