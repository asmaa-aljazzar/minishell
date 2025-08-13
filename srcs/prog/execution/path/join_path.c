#include "minishell.h"
char *join_path(const char *path, const char *cmd)
{
    char *result;
    int path_len;
    int cmd_len;
    int i, j;

    if (!path || !cmd)
        return (NULL);
    
    path_len = ft_strlen(path);
    cmd_len = ft_strlen(cmd);
    
    result = malloc(path_len + cmd_len + 2); // +2 for '/' and '\0'
    if (!result)
        return (NULL);
    
    i = 0;
    j = 0;
    while (i < path_len)
        result[j++] = path[i++];
    
    if (path_len > 0 && path[path_len - 1] != '/')
        result[j++] = '/';
    
    i = 0;
    while (i < cmd_len)
        result[j++] = cmd[i++];
    
    result[j] = '\0';
    return (result);
}
// // builds a string: dir + "/" + cmd
// char *join_path(const char *path, const char *cmd)
// {
//     size_t    len; 
//     char    *full_path;

//     len = ft_strlen(path) + ft_strlen(cmd) + 2;// +1 for '/' +1 for '\0'
//     full_path = malloc(len);
//     if (!full_path)
//         return NULL;
//     snprintf(full_path, len, "%s/%s", path, cmd); //DEBUGING
//     return (full_path);
// }