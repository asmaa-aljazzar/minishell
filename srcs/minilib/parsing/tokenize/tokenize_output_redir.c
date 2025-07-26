/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_output_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:17:47 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 23:47:46 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tokenize_output_redir(t_minishell *minishell, int *k, int *i)
{
	if (minishell->input[*i + 1] == '>')
		handle_output_append_redir(minishell, k, i);
	else
		handle_output_file_redir(minishell, k, i);
}
