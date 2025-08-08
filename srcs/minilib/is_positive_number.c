#include "minishell.h"

// if the string is all positive numbers return 1 else return 0
int is_positive_number(const char *s)
{ 
	if (!s || !*s) // if s is null or s[0] is '\0'.
		return 0; // after this SHLVL will set to 1.
	while (*s) // loop over s
		if (!ft_isdigit(*s++)) // if there is char or `-` return
			return 0;
	return 1; // its positive
}