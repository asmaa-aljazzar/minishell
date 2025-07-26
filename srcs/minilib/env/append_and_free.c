/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 12:00:27 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 12:01:17 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void append_and_free(char **result, char *to_add)
{
    char *temp = *result;
    *result = ft_strjoin(*result, to_add);
    free(temp);
    free(to_add);
}