/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_file_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:42:04 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:48:19 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_input_file_redir(t_minishell *minishell, int *k, int *i)
{
	minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
	if (!minishell->tok[*k])
		ft_exit(minishell, "Memory allocation failed", 1);
	minishell->tok[*k]->word = ft_strdup("<");
	minishell->tok[*k]->type = INPUT_FILE;
	minishell->tok[*k]->qtype = QUOTE_NONE;
	(*k)++;
	(*i)++;
}