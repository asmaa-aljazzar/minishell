/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:49:07 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/20 17:48:12 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"   // ensure libft.h is included inside this

static char *get_env_value(t_env *env, const char *var)
{
    while (env)
    {
        if (ft_strncmp(env->name, var, ft_strlen(env->name) + 1) == 0)
            return env->value;
        env = env->next;
    }
    // Not found → expand to empty string
    return "";
}

char *expand_variable(t_minishell *minishell, char *token)
{
    char    *result = ft_strdup("");
    size_t  i = 0;
    size_t  start;
    char    *temp;
    char    *var_name;
    char    *value;
    char    *literal;

    if (!result || !token)
        return NULL;

    while (token[i])
    {
        if (token[i] == '$')
        {
            i++;
            start = i;
            while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
                i++;
            var_name = ft_substr(token, start, i - start);
            value = get_env_value(minishell->env, var_name);
            free(var_name);
            temp = result;
            result = ft_strjoin(result, value);
            free(temp);
        }
        else
        {
            start = i;
            while (token[i] && token[i] != '$')
                i++;
            literal = ft_substr(token, start, i - start);
            temp = result;
            result = ft_strjoin(result, literal);
            free(temp);
            free(literal);
        }
    }
    return result;
}
