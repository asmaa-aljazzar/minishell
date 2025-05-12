/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:31:47 by aaljazza          #+#    #+#             */
/*   Updated: 2024/09/28 13:32:14 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"
/*
* Fill memory bytes by zeros
*/
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = (char *) s;
	while (i < n)
	{
		cpy[i] = '\0';
		i++;
	}
}
