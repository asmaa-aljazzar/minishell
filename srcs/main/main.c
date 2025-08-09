#include "minishell.h"

int main(int ac, char **av, char **environ)
{
	t_minishell ms; // t_minishell struct
	(void) ac;
	(void) av;
	setup_signals_parent();
	init (&ms, environ);
	// //! Debug
	// debug_print_env_list(ms.env);
	// debug_print_envp_array (ms.envp);
	// //!
	main_loop (&ms); // go to the main loop // todo
	rl_clear_history (); // clear history before exit the shell
	return (0);
}
