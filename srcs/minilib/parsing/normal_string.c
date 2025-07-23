/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:14:49 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/23 16:54:33 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void normal_string(t_minishell *minishell, int *k, int *i, int glued)
{
    char *word;
    int size;
    int start = *i;
    
    // Move glued assignment AFTER token allocation
    
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
    word = calloc(1, size + 1);
    if (!word)
        ft_exit(minishell, "Memory allocation failed", 1);
        
    ft_strlcpy(word, &minishell->input[start], size + 1);
    
    // Allocate and initialize the token structure FIRST
    minishell->tok[*k] = calloc(1, sizeof(t_token));
    if (!minishell->tok[*k])
    {
        free(word);  // Don't forget to free word on failure
        ft_exit(minishell, "Memory allocation failed", 1);
    }
        
    // NOW set all token fields (including glued)
    minishell->tok[*k]->word = word;
    minishell->tok[*k]->type = INUPT_WORD;
    minishell->tok[*k]->qtype = QUOTE_NONE;
    minishell->tok[*k]->glued = glued;  // Moved here
    
    (*k)++;
}