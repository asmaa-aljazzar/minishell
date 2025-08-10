
#include "minishell.h"

char    *find_cmd_path( char *cmd,char *path_env)
{
    char    *full_path;
    char    *token;
    
    token = strtok(path_env, ":");
    while (token)
    {
        full_path = join_path(token, cmd);
        if (!full_path)
                return NULL;
        if (is_executable(full_path))
            return full_path; // found it
        free(full_path);
        token = strtok(NULL, ":");
    }
    return NULL;
}