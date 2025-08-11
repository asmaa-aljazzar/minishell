/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:11:01 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:11:01 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
* The porpose of memset is to fill the memeory 
* with a single byte repeated accross all positions 
* each byte in memory must be assigned the same value
*/
void	*ft_memset(void *ptr, int value, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)ptr;
	while (len > 0)
	{
		*temp++ = (unsigned char)value;
		len--;
	}
	return (ptr);
}
