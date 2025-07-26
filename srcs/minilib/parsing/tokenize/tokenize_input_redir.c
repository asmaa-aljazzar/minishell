/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:17:12 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:48:27 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tokenize_input_redir(t_minishell *minishell, int *k, int *i)
{
	if (minishell->input[*i] == '<')
	{
		if (minishell->input[*i + 1] == '<')
			handle_heredoc_redir(minishell, k, i);
		else
			handle_input_file_redir(minishell, k, i);
	}
	else if (minishell->input[*i] == '>')
		tokenize_output_redir(minishell, k, i);
}
