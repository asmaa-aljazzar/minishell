/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_more_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:35:51 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 02:41:40 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_more_redirections(t_token **tokens, int start_index, t_type t1, t_type t2)
{
	int i = start_index;
	while (tokens[i])
	{
		if (tokens[i]->type == t1 || tokens[i]->type == t2)
			return 1;
		i++;
	}
	return 0;
}