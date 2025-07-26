/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_and_merge.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:21:44 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:22:08 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void advance_and_merge(t_minishell *minishell, t_token **orig, int *i, int k)
{
	while (orig[*i + 1]
		&& minishell->tok[k]->type == INUPT_WORD
		&& orig[*i + 1]->type == INUPT_WORD
		&& orig[*i + 1]->glued == 1)
	{
		merge_two_tokens(minishell, minishell->tok[k], orig[*i + 1]);
		(*i)++;
	}
}