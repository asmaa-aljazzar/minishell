/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_two_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:24:57 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:29:42 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void merge_two_tokens(t_minishell *minishell, t_token *dst, t_token *src)
{
	char *joined_word = ft_strjoin(dst->word, src->word);
	if (!joined_word)
		ft_exit(minishell, "malloc failed", 1);
	free(dst->word);
	dst->word = joined_word;
	free_token(src);
}