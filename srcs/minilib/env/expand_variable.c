/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:49:07 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 03:28:36 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // ensure libft.h is included inside this

void append_and_free(char **result, char *to_add)
{
    char *temp = *result;
    *result = ft_strjoin(*result, to_add);
    free(temp);
    free(to_add);
}
char *get_env_value(t_env *env, const char *var)
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
char *append_result(char *old_result, char *value)
{
	char *temp = old_result;
	char *new_result = ft_strjoin(old_result, value);
	free(temp);
	return new_result;
}

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
void handle_dollar(t_minishell *minishell, char *token, size_t *i, char **result)
{
    char *value = NULL;
    int should_free = 0;

    (*i)++;
    if (token[*i] == '?')
    {
        value = ft_itoa(minishell->exit_code);
        should_free = 1;
        (*i)++;
    }
    else
        value = extract_var_value(minishell, token, i);

    *result = append_result(*result, value);

    if (should_free)
        free(value);
}



char *expand_variable(t_minishell *minishell, char *token)
{
    size_t i = 0;
    char *result;
    char *temp;

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
