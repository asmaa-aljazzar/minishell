/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quoted_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:45:34 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:49:19 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_quoted_token(t_minishell *ms, int *k, char *word, char quote, int glued)
{
	ms->tok[*k] = ft_calloc(1, sizeof(t_token));
	if (!ms->tok[*k])
	{
		free(word);
		ft_exit(ms, "Memory allocation failed", 1);
	}
	ms->tok[*k]->word = word;
	ms->tok[*k]->type = INUPT_WORD;
	ms->tok[*k]->qtype = (quote == '"') ? QUOTE_DOUBLE : QUOTE_SINGLE;
	ms->tok[*k]->glued = glued;
	(*k)++;
}