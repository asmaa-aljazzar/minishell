#include "minishell.h"

t_env *create_env_node(t_minishell *ms, char *environ)
{
    char *equal;
    t_env *node;

    equal = ft_strchr(environ, '='); // Srearch for '='
    if (!equal)
        return NULL; // there is no = in this element
    node = malloc(sizeof(t_env)); //! allocate for node 
    if (!node)
        ft_exit(ms, "Memory allocation failed", 1);
    node->name = ft_substr(environ, 0, equal - environ); // extract the name from index 0 into index of '='
    node->value = ft_strdup(equal + 1); // from equal to the end this is the value 'dup it'
    node->next = NULL;
    return node;
}