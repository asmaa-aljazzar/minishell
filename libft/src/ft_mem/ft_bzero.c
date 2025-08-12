/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:09:57 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:09:57 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
