/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:49:07 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 12:56:53 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_variable(t_minishell *minishell, char *token)
{
    size_t i;
    char *result;
    char *temp;

    i = 0;
    result = ft_strdup("");
    if (!result || !token)
        return NULL;
    while (token[i])
    {
        if (token[i] == '$')
            handle_dollar(minishell, token, &i, &result);
        else
        {
            temp = extract_literal(token, &i);
            append_and_free(&result, temp);
        }
    }
    return result;
}
