
#include "minishell.h"

char	*get_env_value(t_env *env, const char *var, char *argv)
{
	if (argv && ft_strcmp(var, "0") == 0)
		return (argv);
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name) + 1) == 0)
			return (env->value); // get the value from the name
		env = env->next;
	}
	return ("");
}