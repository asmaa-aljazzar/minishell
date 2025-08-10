#include "minishell.h"

void print_slowly(const char *line)
{
    int i;
    i = 0;
    while (line[i])
    {
        write(1, &line[i], 1);
        usleep(500);
        i++;
    }
}