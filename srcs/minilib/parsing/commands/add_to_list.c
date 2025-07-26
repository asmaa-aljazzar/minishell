/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:49:28 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 02:49:30 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// [ free(old_list) ] Only pointer, not the strings inside

char **add_to_list(char **old_list, char *value)
{
	int len;
	len = 0;
	while (old_list && old_list[len])
		len++;
	char **new_list = malloc(sizeof(char *) * (len + 2));
	if (!new_list)
		return NULL;
	for (int i = 0; i < len; i++)
		new_list[i] = old_list[i];
	new_list[len] = ft_strdup(value);
	new_list[len + 1] = NULL;
	free(old_list); 
	return new_list;
}