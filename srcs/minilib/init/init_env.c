/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:48:52 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/24 14:34:13 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// System environment (environ)  -->  Your t_env linked list
//           (readonly)          -->  (owned by your shell)

t_env *init_env(t_minishell *minishell, char **environ)
{
    t_env *head;
    t_env *tail;
    t_env *new_node;
    char *equalOpPosition;
    int i;

    i = 0;
    head = NULL;
    while (environ[i])
    {
        equalOpPosition = ft_strchr(environ[i], '=');
        if (!equalOpPosition)
            continue;
        new_node = (t_env *)malloc(sizeof(t_env));
        if (!new_node)
            ft_exit(minishell, "Memory allocation failed", 1);
        new_node->name = ft_substr(environ[i], 0, equalOpPosition - environ[i]);
        new_node->value = ft_strdup(equalOpPosition + 1);
        new_node->next = NULL;
        if (!head)
            head = new_node;
        else
            tail->next = new_node;
        tail = new_node;
        i++;
    }
    return head;
}