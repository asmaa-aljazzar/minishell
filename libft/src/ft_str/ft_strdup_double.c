/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:14:58 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:30:19 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_strdup_double(char **src)
{
	int		i;
	char	**copy;

	i = 0;
	while (src[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = ft_strdup(src[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
