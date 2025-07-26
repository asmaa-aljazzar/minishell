/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_normal_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:23:22 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 14:27:09 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *allocate_normal_word(t_minishell *ms, int start, int len)
{
	char *word = calloc(1, len + 1);
	if (!word)
		ft_exit(ms, "Memory allocation failed", 1);

	ft_strlcpy(word, &ms->input[start], len + 1);
	return word;
}