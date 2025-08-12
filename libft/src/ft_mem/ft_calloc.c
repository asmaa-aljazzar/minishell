/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:10:09 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:11:33 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
* to allocate a specified amount of memory and then initialize it to zero
*/
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	temp = malloc(count * size);
	if (!temp)
		return (NULL);
	while (i < count * size)
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}
