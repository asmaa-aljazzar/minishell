/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:49:01 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/21 11:51:40 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export_builtin(t_minishell *minishell)
{
    t_token **tokens;
    char *equal_position;
    int i;

    tokens = minishell->tok;
    if (!tokens || !tokens[0] || !tokens[0]->word)
        return;
    if (ft_strncmp(tokens[0]->word, "export", ft_strlen("export") + 1) == 0)
    {
        if (!tokens[1])
        {
            // print_sorted_env(&minishell); // Format: declare -x KEY="VALUE"
            return;
        }
        i = 1;
        while (tokens[i])
        {
            if (tokens[i]->word)
            {
                equal_position = ft_strchr(tokens[i]->word, '=');
                if (equal_position)
                {
                    // update_or_add_env(&minishell, tokens[i]->word, equal_position); // Todo
                }
                else
                {
                    // export_without_value(&minishell, tokens[i]->word); // Todo
                }
                i++;
            }
        }
    }
}
