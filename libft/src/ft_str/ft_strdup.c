/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:15:07 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:15:09 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
* function allocates sufficient memory for a copy of the string s1.
* does the copy, and returns a pointer to it.
* The pointer may subsequently be used as an argument to the function free(3).
*/
char	*ft_strdup(const char *s1)
{
	unsigned int	len;
	char			*dst;

	len = ft_strlen(s1) + 1;
	dst = malloc(len);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s1, len);
	return (dst);
}
