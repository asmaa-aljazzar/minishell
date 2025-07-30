/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:03:50 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/28 22:03:58 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void cd_builtin(t_minishell *shell)
// {
//     t_command *cmd = shell->cmd;
//     char *path;
//     int result;
//      printf("call cd\n");

//     if (!cmd->argv[1])  // No argument: use $HOME
//     {
//         path = get_env_value(shell->env, "HOME");
//         if (!path)
//         {
//             printf("cd: HOME not set\n");
//             shell->exit_code = 1;
//             return;
//         }
//     }
//     else
//         path = cmd->argv[1];

//     result = chdir(path);
//     if (result == -1)
//     {
//         perror("cd");
//         shell->exit_code = 1;
//     }
//     else
//         shell->exit_code = 0;
// }

// void cd_builtin(t_minishell *shell)
// {
//     t_command *cmd = shell->cmd;
//     char *path;
//     char *oldpwd;
//     char *cwd;
//     int result;

//     oldpwd = get_env_value(shell->env, "PWD");

//     if (!cmd->argv[1])  // No argument: use $HOME
//     {
//         path = get_env_value(shell->env, "HOME");
//         if (!path || !*path)
//         {
//             printf("cd: HOME not set\n");
//             shell->exit_code = 1;
//             return;
//         }
//     }
//     else if (ft_strncmp(cmd->argv[1], "-", 2) == 0) // cd -
//     {
//         path = get_env_value(shell->env, "OLDPWD");
//         if (!path || !*path)
//         {
//             printf("cd: OLDPWD not set\n");
//             shell->exit_code = 1;
//             return;
//         }
//         printf("%s\n", path);
//     }
//     else
//         path = cmd->argv[1];

//     result = chdir(path);
//     if (result == -1)
//     {
//         perror("cd");
//         shell->exit_code = 1;
//         return;
//     }

//     // update OLDPWD
//     if (oldpwd)
//         update_env_value(shell->env, "OLDPWD", oldpwd);

//     // update PWD
//     cwd = getcwd(NULL, 0);
//     if (cwd)
//     {
//         update_env_value(shell->env, "PWD", cwd);
//         free(cwd);
//     }

//     shell->exit_code = 0;
// }


