/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:52:12 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 14:06:21 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_tokens(t_minishell *minishell)
{
	size_t len = ft_strlen(minishell->input);
	int i = 0;
	int k = 0;

	minishell->tok = ft_calloc(len + 1, sizeof(t_token *));
	if (!minishell->tok)
		ft_exit(minishell, "malloc failed", 1);

	while (minishell->input[i])
		process_token(minishell, &k, &i);

	minishell->tok[k] = NULL;
	minishell->tokens_count = k;
}


