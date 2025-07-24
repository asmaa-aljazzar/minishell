/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:13:32 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/14 06:13:39 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void free_2d(char **arr)
// {
//     int i;

//     if (!arr)
//         return;
//     i = 0;
//     while (arr[i])
//     {
//         free(arr[i]);
//         arr[i] = NULL;
//         i++;
//     }
//     free(arr);
// }
void free_2d(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);  // <-- only free if you own these strings separately!
        arr[i] = NULL;
        i++;
    }
    free(arr);
}
