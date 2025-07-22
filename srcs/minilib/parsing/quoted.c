/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:15:41 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/22 16:08:04 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void quoted(t_minishell *minishell, int *k, int *i)
{
    int size;
    int start;
    char *word;
    char quote;

    if (minishell->input[*i] == '\'' || minishell->input[*i] == '"')
    {
        quote = minishell->input[(*i)++];
        start = *i;
        while (minishell->input[*i] && minishell->input[*i] != quote)
            (*i)++;
        if (minishell->input[*i] != quote)
            ft_putendl_fd("Syntax error: unmatched quote", STDERR_FILENO);
        size = *i - start;
        word = malloc(size + 1);
        if (!word)
            ft_exit(minishell, "Memory allocation failed", 1);

        ft_strlcpy(word, &minishell->input[start], size + 1);

        // Allocate the token structure
        minishell->tok[*k] = calloc(1, sizeof(t_token));
        if (!minishell->tok[*k])
            ft_exit(minishell, "Memory allocation failed", 1);

        minishell->tok[*k]->word = word;
        minishell->tok[*k]->type = INUPT_WORD;
        if (quote == '"')
            minishell->tok[*k]->qtype = QUOTE_DOUBLE;
        else
            minishell->tok[*k]->qtype = QUOTE_SINGLE;
        (*k)++;
        (*i)++;
    }
    else
    {
        normal_string(minishell, k, i); // Updated to match your likely implementation
    }
}