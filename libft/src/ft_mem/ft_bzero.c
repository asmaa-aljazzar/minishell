#include "../../includes/libft.h"
/*
* Fill memory bytes by zeros
*/
void	ft_bzero(void *ptr, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)ptr;
	while (len > 0)
	{
		*temp++ = 0;
		len--;
	}
}
