/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:34:15 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:27:25 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void merge_words(t_minishell *minishell)
{
	t_token **orig;
	int i;
	int k;
    
    i = 0;
    k = 0;
	if (!minishell || !minishell->tok)
		return;
	orig = minishell->tok;
	while (orig[i])
	{
		minishell->tok[k] = orig[i];
		advance_and_merge(minishell, orig, &i, k);
		k++;
		i++;
	}
	minishell->tok[k] = NULL;
	minishell->tokens_count = k;
}
