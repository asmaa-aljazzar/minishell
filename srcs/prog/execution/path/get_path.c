
#include "minishell.h"

char    *get_path(t_minishell *shell)
{
    char    *path_env;
    char    *path_copy;
    char    *path;
    t_command   *cmd ;

    path_env = NULL;
    path_copy = NULL;
    cmd = shell->cmd;
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (NULL);
    if((path =already_path(cmd->argv[0]))) //if input is already  /usr/bin/cat
    {
            if(!path)
                return (NULL);
        return(path);
    }
    path_env = find_path(shell->env); // get raw PATH string
    if (!path_env)
        return (NULL);
    path_copy = ft_strdup(path_env);
    if (!path_copy)
        return (NULL);
    path = find_cmd_path(cmd->argv[0], path_copy);
        free(path_copy);
    return (path);
}
