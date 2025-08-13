#include "minishell.h"

t_env	*init_env(t_minishell *minishell, char **environ)
{
	int	i;
	t_env *head;     // pointer to the first node
	t_env *tail;     // pointer the last node
	t_env *new_node; // new env var

	head = NULL;
	tail = NULL;
	i = 0;
	while (environ[i])
	{
		new_node = create_env_node(minishell, environ[i]);// creat a new node for environ[i] 
		if (!new_node)
			return (NULL);
		append_env_node(new_node, &head, &tail); // append the node /
		i++;                                     // go to the next variable
	}
	return (head); // return a pointer to the first node of env linked list
}
