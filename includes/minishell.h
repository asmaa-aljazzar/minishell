#ifndef  MINISHELL_H
# define MINISHELL_H

//***[ Libraries ]***
//- internal
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
//- external
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <term.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>

// ***[ Macros ]***
# define PROMPT "\e[35mminishell\e[32m$ \e[0m"
//***[ Structures ]***

// Each Command line has a node
typedef struct s_cmd {
    char **args;          // ["grep", "main"]
    char *infile;         // for < and <<
    char *outfile;        // for > or >>
    int   append;         // 1 if >>, 0 if >
    struct s_cmd *next;   // next command in a pipe
} t_cmd;


//***[ Functions Definition ]***
void  parse_and_execute (char *input, t_cmd *cmd);
// char  **parse_and_execute (char *input); //? for test
void    init_cmd (t_cmd *cmd);
#endif

