/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:12:11 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 13:35:35 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_file_list(char **list)
{
    if (!list)
        return;
    for (int i = 0; list[i]; i++)
        free(list[i]);
    free(list);
}
