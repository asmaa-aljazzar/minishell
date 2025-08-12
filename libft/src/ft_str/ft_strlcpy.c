/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:15:45 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:15:47 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
* Copy src to dst to until reach specific size for dst 
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;

	srcsize = ft_strlen(src);
	if (dstsize > 0)
	{
		if (dstsize > srcsize + 1)
		{
			ft_memcpy(dst, src, srcsize +1);
		}
		else
		{
			ft_memcpy(dst, src, dstsize - 1);
			dst[dstsize - 1] = '\0';
		}
	}
	return (srcsize);
}
