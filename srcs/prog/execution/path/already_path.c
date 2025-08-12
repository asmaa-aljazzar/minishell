
#include "minishell.h"

char *already_path(char *cmd)
{
    char    *cmd_found;
    cmd_found = NULL;
    if (ft_strchr(cmd, '/'))
    {
        if (is_executable(cmd))
        {
            cmd_found = ft_strdup(cmd);
            if(!cmd_found)
                return (NULL);
            return (cmd_found);
        }
    }
    return (NULL);
}