/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_result.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:56:02 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 11:56:13 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *append_result(char *old_result, char *value)
{
	char *temp = old_result;
	char *new_result = ft_strjoin(old_result, value);
	free(temp);
	return new_result;
}