#include "minishell.h"

void debug_print_env_list(t_env *env)
{
    t_env *current = env;
    int index = 0;

    if (!env)
    {
        printf("[debug] Environment linked list is NULL.\n");
        return;
    }

    printf("[debug] Environment linked list contents:\n");
    while (current)
    {
        printf("  [%d] name: \"%s\", value: \"%s\"\n",
               index,
               current->name ? current->name : "(null)",
               current->value ? current->value : "(null)");
        current = current->next;
        index++;
    }
}
