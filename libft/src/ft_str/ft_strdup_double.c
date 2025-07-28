/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:35:08 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/28 18:35:31 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char **ft_strdup_double(char **src)
{
    int i = 0;
    char **copy;

    while (src[i])
        i++;
    copy = malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return NULL;
    i = 0;
    while (src[i])
    {
        copy[i] = ft_strdup(src[i]);
        i++;
    }
    copy[i] = NULL;
    return copy;
}