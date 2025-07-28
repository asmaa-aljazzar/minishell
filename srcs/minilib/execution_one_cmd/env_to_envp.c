/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:36:29 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/27 01:56:08 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **env_to_envp(t_env *env)
// {
//     int count = 0;
//     int i = 0;
//     t_env *tmp = env;
//     char **envp;
//     char *line;
//     char *full_line;

//     while (tmp)
//     {
//         count++;
//         tmp = tmp->next;
//     }
//     envp = malloc(sizeof(char *) * (count + 1));
//     if (!envp)
//         return NULL;
//     tmp = env;
//     while (tmp)
//     {
//         line = ft_strjoin(tmp->name, "=");
//         if (tmp->value)
//             full_line = ft_strjoin(line, tmp->value);
//         else
//             full_line = ft_strjoin(line, "");
//         free(line);
//         envp[i++] = full_line;
//         tmp = tmp->next;
//     }
//     envp[i] = NULL;
//     return envp;
// }

