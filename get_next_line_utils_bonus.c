#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t		total_size;
	char		*ptr;
	int			i;

	total_size = nmemb * size;
	if (size != 0 && total_size / size != nmemb)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total_size)
		ptr[i++] = 0;
	return (ptr);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

static size_t	ft_malloc_size(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	malloc_size;

	len_s = ft_strlen(s);
	if (len_s < start)
		malloc_size = 0;
	else if (len_s < start + len)
		malloc_size = len_s - start;
	else
		malloc_size = len;
	return (malloc_size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	size_t		i;
	size_t		malloc_size;

	if (!s)
		return (NULL);
	malloc_size = ft_malloc_size(s, start, len);
	ptr = (char *)malloc(sizeof(char) * (malloc_size + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	if (malloc_size > 0)
	{
		while (s[start] && i < len)
		{
			ptr[i] = s[start];
			start++;
			i++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = c % 256;
	while (s[i])
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (c == 0 && s[i] == '\0')
		return (i);
	return (-1);
}