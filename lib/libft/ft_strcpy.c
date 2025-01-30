#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char *start;
	
	start = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}
