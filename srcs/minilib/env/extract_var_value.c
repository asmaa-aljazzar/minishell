/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:53:32 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 11:53:43 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extract_var_value(t_minishell *minishell, char *token, size_t *i)
{
    size_t start = *i;
    while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
        (*i)++;

    char *var_name = ft_substr(token, start, *i - start);
    char *value = get_env_value(minishell->env, var_name);
    free(var_name);
    return value;
}