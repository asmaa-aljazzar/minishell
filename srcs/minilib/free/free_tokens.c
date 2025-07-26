/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 06:00:26 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 13:11:31 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tokens(t_token **tokens)
{
    int i = 0;

    if (!tokens)
        return;
    while (tokens[i])
    {
        free(tokens[i]->word);  
        free(tokens[i]);        
        i++;
    }
    free(tokens);
}