#include "minishell.h"

void increase_SHLVL_var(t_minishell *ms, t_env *env)
{
	char *old; // old value of SHLVL
	int lvl; // This will be the level of the shell
	char *new;

	old = get_env_value(env, "SHLVL"); // get the old value of SHLVL // todo
	if (is_positive_number(old)) // If the value is positive
		lvl = ft_atoi(old) + 1;	// add one to it
	else
		lvl = 1; // reset to 1 if it is negative
	new = ft_itoa(lvl); // set in new var to free after itoa'
	if (!new)
		return (NULL);
	update_env_var(ms, "SHLVL", new); // update env linked list //todo
	update_envp_array(ms, "SHLVL", new); // update envp array //todo
	free(new); // free after ft_itoa
}