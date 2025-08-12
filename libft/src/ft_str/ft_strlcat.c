/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:15:31 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:15:39 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
* Concatenates the source string (src)
* to the destination string (dst)
* ensuring that the final string fits
* within the buffer size specified by dstsize.
* It returns the length of the concatenated strings: 
* the original length of dst plus the length of src.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		dstlen = dstsize;
	if (dstlen == dstsize)
		return (dstsize + srclen);
	if (srclen < dstsize - dstlen)
	{
		ft_memcpy(dst + dstlen, src, srclen + 1);
	}
	else
	{
		ft_memcpy(dst + dstlen, src, dstsize - dstlen - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dstlen + srclen);
}
