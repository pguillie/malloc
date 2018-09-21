#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*u;

	u = (unsigned char *)s;
	while (n--)
		u[n] = c;
	return (s);
}
