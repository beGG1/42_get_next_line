/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshabali <sshabali@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:39:00 by sshabali          #+#    #+#             */
/*   Updated: 2024/12/07 23:39:01 by sshabali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (ft_free(&s1));
	i = 0;
	j = 0;
	while (s1[j])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&((char *)s)[i]);
	return (0);
}

static size_t	ft_malloc_size(char *s, unsigned int start, size_t len)
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

char	*ft_substr(char *s, unsigned int start, size_t len)
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
