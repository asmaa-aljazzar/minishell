
#include "minishell.h"
// void	if_input_files_heredoc(t_minishell *minishell, t_token *token,
// 		t_command **cmd, int *i)
// {
// 	char	*file;

// 	if (token->type == INPUT_FILE || token->type == INPUT_HEREDOC)
// 	{
// 		if (minishell->tok[(*i) + 1])
// 		{
// 			file = minishell->tok[++(*i)]->word;
// 			(*cmd)->input_files = add_to_list((*cmd)->input_files, file);
// 		}
// 	}
// }

t_redirection *create_redir(char *file, int type)
{
	t_redirection *new_redir;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return (NULL);
	new_redir->file = file;
	new_redir->type = type;
	new_redir->heredoc_fd = -1;
	new_redir->next = NULL;
	new_redir->prev = NULL;
	return (new_redir);
}

int add_redirection(t_minishell *minishell, t_redirection **root, t_token *token, char *file)
{
	t_redirection *new_redir;
	t_redirection *current;

	new_redir = create_redir(file, token->type);
	if (!new_redir)
		return (0);
	if (!(*root))
		*root = new_redir;
	else
	{
		current = *root;
		while (current->next)
			current = current->next;
		current->next = new_redir;
		new_redir->prev = current;
		// if (new_redir->prev->heredoc_fd != -1)
		// {
		// 	close(new_redir->prev->heredoc_fd);
		// 	new_redir->prev->heredoc_fd = -1; // Reset fd after closing
		// }
	}
	if (new_redir->type == T_HEREDOC)
	{
		new_redir->heredoc_fd = process_heredoc(minishell, file);
		// fprintf(stderr, "---->%d \n", new_redir->heredoc_fd);
	}
	return (1);
}

int is_redirect(t_token *token)
{
	if (token->type == T_INPUT 
		|| token->type == T_HEREDOC 
		|| token->type == T_OUTPUT 
		|| token->type == T_APPEND)
		return (1);
	return (0);
}

int fill_redirections(t_minishell *minishell, t_token *token,
		t_command **cmd, int *i)
{
	char	*file;

	if (is_redirect(token))
	{
		if (minishell->tok[(*i) + 1])
		{
			file = minishell->tok[++(*i)]->word;
			add_redirection(minishell, &((*cmd)->redir), token, file);
		}
	}
	return (0);
}

void print_re(t_command *cmd)
{
	t_redirection *re;

	re = cmd->redir;
	while (re)
	{
		fprintf(stderr, "%d   ", re->type);
		if (re->type == T_HEREDOC)
			fprintf(stderr, "%d\n", re->heredoc_fd);
		else
			fprintf(stderr, "%s\n", re->file);
		re = re->next;
	}
}

void	tokens_to_commands(t_minishell *minishell)
{
	t_command	*cmd;
	t_token		**tokens;
	int			i;
	int			argc;

	cmd = minishell->cmd;
	i = 0;
	argc = 0;
	tokens = minishell->tok;
	while (tokens[i])
	{
		if_output_pipe(tokens[i], &cmd, &argc);
		fill_redirections(minishell, tokens[i], &cmd, &i);
		if (tokens[i]->type == T_WORD)
			cmd->argv[argc++] = tokens[i]->word;
		i++;
	}
	// print_re(cmd);
	if (cmd && cmd->argv)
		cmd->argv[argc] = NULL;
}
