/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:14:49 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/14 05:57:51 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void normal_string(t_minishell *minishell, int *k, int *i)
{
    char *word;
    int size;
    int start = *i;

    while (minishell->input[*i] && minishell->input[*i] != ' ' 
        && minishell->input[*i] != '\'' && minishell->input[*i] != '"' 
        && minishell->input[*i] != '>' && minishell->input[*i] != '<' 
        && minishell->input[*i] != '|')
        (*i)++;

    size = *i - start;
    
    // Skip empty tokens
    if (size == 0)
        return;
        
    // Allocate memory for the word
    word = calloc (1, size + 1);
    if (!word)
        ft_exit(minishell, "Memory allocation failed", 1);
        
    ft_strlcpy(word, &minishell->input[start], size + 1);
    
    // Allocate and initialize the token structure
    minishell->tok[*k] = calloc(1, sizeof(t_token));
    if (!minishell->tok[*k])
        ft_exit(minishell, "Memory allocation failed", 1);
        
    // Set all token fields
    minishell->tok[*k]->word = word;
    minishell->tok[*k]->type = INUPT_WORD;  // Using your enum value
    minishell->tok[*k]->qtype = QUOTE_NONE; // Not quoted
    
    (*k)++;
}