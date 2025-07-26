/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output_append_redir.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:42:32 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:47:15 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_output_append_redir(t_minishell *minishell, int *k, int *i)
{
	minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
	if (!minishell->tok[*k])
		ft_exit(minishell, "Memory allocation failed", 1);
	minishell->tok[*k]->word = ft_strdup(">>");
	minishell->tok[*k]->type = OUTPUT_APPEND;
	minishell->tok[*k]->qtype = QUOTE_NONE;
	(*k)++;
	(*i) += 2;
}