#include <stdlib.h>
#include "minishell.h"

/* must be at top of main.c: */
static int is_positive_number(const char *s)
{
	if (!s || !*s)
		return 0;
	while (*s)
		if (!ft_isdigit(*s++))
			return 0;
	return 1;
}

int main(int ac, char **av, char **environ)
{
	t_minishell ms;
	(void)ac;
	(void)av;

	init(&ms);
	ms.envp = ft_strdup_double(environ);
	ms.env = init_env(&ms, environ);

	{
		char *old = get_env_value(ms.env, "SHLVL");
		int lvl;

		if (is_positive_number(old))
			lvl = ft_atoi(old) + 1;
		else
			lvl = 1;
		char *new = ft_itoa(lvl);

		update_env_var(&ms, "SHLVL", new);	  /* linked list */
		update_envp_array(&ms, "SHLVL", new); /* envp[] array */

		free(new);
	}

	main_loop(&ms);
	rl_clear_history();
	return 0;
}