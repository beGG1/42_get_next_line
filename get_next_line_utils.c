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