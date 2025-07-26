/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_literal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:25:39 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 03:27:43 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extract_literal(char *token, size_t *i)
{
    size_t start = *i;
    while (token[*i] && token[*i] != '$')
        (*i)++;
    return ft_substr(token, start, *i - start);
}