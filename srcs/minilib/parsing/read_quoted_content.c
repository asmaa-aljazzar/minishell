/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_quoted_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:46:10 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:49:04 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_quoted_content(t_minishell *ms, int *i, char quote)
{
	int start = ++(*i);
	while (ms->input[*i] && ms->input[*i] != quote)
		(*i)++;

	if (ms->input[*i] != quote)
	{
		ft_putendl_fd("Syntax error: unmatched quote", STDERR_FILENO);
		return NULL;
	}
	int size = *i - start;
	char *word = malloc(size + 1);
	if (!word)
		ft_exit(ms, "Memory allocation failed", 1);
	ft_strlcpy(word, &ms->input[start], size + 1);
	return word;
}
