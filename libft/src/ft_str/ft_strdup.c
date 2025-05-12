/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:39:22 by aaljazza          #+#    #+#             */
/*   Updated: 2024/09/28 13:39:30 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

/*
* function allocates sufficient memory for a copy of the string s1.
* does the copy, and returns a pointer to it.
* The pointer may subsequently be used as an argument to the function free(3).
*/
char	*ft_strdup(const char *s)
{
	char	*x;
	int		len;
	int		i;

	len = ft_strlen(s);
	x = (char *) malloc(len + 1);
	if (!x)
		return (NULL);
	i = 0;
	while (i < len)
	{
		x[i] = (char) s[i];
		i++;
	}
	x[i] = '\0';
	return (x);
}
