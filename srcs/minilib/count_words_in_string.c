#include "minishell.h"
int count_words_in_string(char *str)
{
    int count;
    int in_word;
    int i;

    i = 0;
    count = 0;
    in_word = 0;
    if (!str)
        return 0;
    while (str[i])
    {
        if (!is_whitespace(str[i]))
        {
            if (!in_word)
            {
                count++;
                in_word = 1;
            }
        }
        else
        {
            in_word = 0;
        }
        i++;
    }
    return count;
}
