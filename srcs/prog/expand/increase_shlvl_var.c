#include "minishell.h"

int	increase_shlvl_var(t_minishell *ms, t_env *env) 
{
	char	*new;
	char	*old; // old value of SHLVL
	int		lvl;   // This will be the level of the shell

	old = get_env_value(env, "SHLVL", NULL); // get the old value of SHLVL // todo
	if (is_positive_number(old))       // If the value is positive
		lvl = ft_atoi(old) + 1;        // add one to it
	else
		lvl = 1;        // reset to 1 if it is negative
	new = ft_itoa(lvl); // set in new var to free after itoa'
	if (!new)
		return (0);
	if (!update_env_var(ms, "SHLVL", new))
	{
		free(new);
		return (0); // update env linked list
	}
	if (!update_envp_array(ms, "SHLVL", new))
	{
		free(new);
		return (0);
	}
	free(new); // free after ft_itoa
	return (1);
}

