/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:14:41 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:14:43 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
* Search for specific char ( first appearing )
* in a string and return pointer to it
*/
char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			ch;

	i = 0;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == ch)
		return ((char *)&s[i]);
	return (NULL);
}
