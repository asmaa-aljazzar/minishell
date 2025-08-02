#include "../../includes/libft.h"
// This function count the number of characters in a string
size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (*str++ != '\0')
	{
		counter++;
	}
	return (counter);
}
