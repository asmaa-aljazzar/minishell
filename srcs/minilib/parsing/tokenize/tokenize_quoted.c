/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:15:41 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:58:29 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tokenize_quoted(t_minishell *ms, int *k, int *i, int glued)
{
	if (ms->input[*i] == '\'' || ms->input[*i] == '"')
	{
		char quote = ms->input[*i];
		char *word = read_quoted_content(ms, i, quote);
		if (!word)
			return;
		create_quoted_token(ms, k, word, quote, glued);
		(*i)++;
	}
	else
	{
		tokenize_normal_string(ms, k, i, glued);
	}
}

