#include "minishell.h"

void debug_print_env(t_minishell *shell)
{
    t_env *current;
    int count = 0;

    if (!shell || !shell->env)
    {
        printf("=== DEBUG ENV LIST ===\n");
        printf("Environment is NULL or empty!\n");
        printf("=== END DEBUG ===\n");
        return;
    }

    current = shell->env;

    printf("=== DEBUG ENV LIST ===\n");
    while (current)
    {
        printf("[%d] Name: '", count);
        if (current->name)
            printf("%s", current->name);
        else
            printf("NULL");
        printf("', Value: '");
        if (current->value)
            printf("%s", current->value);
        else
            printf("NULL");
        printf("'\n");

        current = current->next;
        count++;
    }
    printf("Total variables: %d\n", count);
    printf("=== END DEBUG ===\n");
}