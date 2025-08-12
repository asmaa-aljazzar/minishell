
#include "minishell.h"

char    *find_path(t_env *env)
{
     while(env)    // find PATH in envp
    {
        if (strncmp(env->name, "PATH", 4) == 0)
            return (env->value);
        env = env->next;
    }
    fprintf(stderr, "PATH not found\n");
    return (NULL);
}