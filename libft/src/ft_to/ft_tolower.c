#include "../../includes/libft.h"
/*
* The function converts an upper-case letter 
* to the corresponding lower-case letter.
*/
int	ft_tolower(int c)
{
	if (c <= 90 && c >= 65)
		return (c + 32);
	return (c);
}
