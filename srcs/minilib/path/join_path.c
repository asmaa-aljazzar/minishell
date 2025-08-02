
#include "minishell.h"
// builds a string: dir + "/" + cmd
char *join_path(const char *path, const char *cmd)
{
    size_t    len; 
    char    *full_path;

    len = ft_strlen(path) + ft_strlen(cmd) + 2;// +1 for '/' +1 for '\0'
    full_path = malloc(len);
    if (!full_path)
        return NULL;
    snprintf(full_path, len, "%s/%s", path, cmd); //DEBUGING
    return (full_path);
}