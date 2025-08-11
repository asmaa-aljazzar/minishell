#include "minishell.h"

void	append_env_node(t_env *new_node, t_env **head, t_env **tail)
{
	if (new_node) // if there is a new node
	{
		if (!*head)           // if no node in list
			*head = new_node; // the head point to the new one
		else
			(*tail)->next = new_node; // the new one set after the last one
		*tail = new_node;             // the last one its the new one
	}
}
