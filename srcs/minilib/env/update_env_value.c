#include "minishell.h"

void update_env_value(t_env *env, const char *name, const char *new_value)
{
    while (env)
    {
        if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
        {
            free(env->value);
            env->value = ft_strdup(new_value);
            return;
        }
        env = env->next;
    }
}
