/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:15:41 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/24 15:21:50 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
void tokenize_quoted(t_minishell *minishell, int *k, int *i, int glued)
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
            {
                ft_putendl_fd("Syntax error: unmatched quote", STDERR_FILENO);
                minishell->exit_code = ERR_SYNTAX_UNMATCHED_QUOTE;
            }
        size = *i - start;
        word = malloc(size + 1);
        if (!word)
            ft_exit(minishell, "Memory allocation failed", 1);

        ft_strlcpy(word, &minishell->input[start], size + 1);

        // Allocate the token structure
        minishell->tok[*k] = calloc(1, sizeof(t_token));
        if (!minishell->tok[*k])
        {
            free(word);
            ft_exit(minishell, "Memory allocation failed", 1);
        }

        minishell->tok[*k]->word = word;
        minishell->tok[*k]->type = INUPT_WORD;
        minishell->tok[*k]->glued = glued;  // Use the passed glued value
        if (quote == '"')
            minishell->tok[*k]->qtype = QUOTE_DOUBLE;
        else
            minishell->tok[*k]->qtype = QUOTE_SINGLE;
        (*k)++;
        (*i)++;
    }
    else
    {
        tokenize_normal_string(minishell, k, i, glued);
    }
}