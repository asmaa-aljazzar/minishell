
#include "minishell.h"

static t_env *create_env_node(t_minishell *minishell, char *env_string);

t_env *init_env(t_minishell *minishell, char **environ)
{
    t_env *head = NULL;
    t_env *tail = NULL;
    t_env *new_node;
    int i = 0;

    while (environ[i])
    {
        new_node = create_env_node(minishell, environ[i]);
        if (new_node)
        {
            if (!head)
                head = new_node;
            else
                tail->next = new_node;
            tail = new_node;
        }
        i++;
    }
    return head;
}

//#### A helper function for init_env function
//- Determine the position of [ = ].
//- Allocate memory for each env node.
//- Extract name and value use (substr, strdup).
static t_env *create_env_node(t_minishell *minishell, char *env_string)
{
    char *equal = ft_strchr(env_string, '=');
    t_env *node;

    if (!equal)
        return NULL;
    node = malloc(sizeof(t_env));
    if (!node)
        ft_exit(minishell, "Memory allocation failed", 1);
    node->name = ft_substr(env_string, 0, equal - env_string);
    node->value = ft_strdup(equal + 1);
    node->next = NULL;
    return node;
}
