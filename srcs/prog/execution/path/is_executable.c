
#include "minishell.h"
// checks if is executable
int is_executable(char *path)
{
    if (access(path, X_OK) == 0)
        return (1);
        
    return (0);
}