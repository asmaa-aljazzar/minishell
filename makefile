**************************************************************************** #


# Color
RESET	=	\033[0m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m


# Standard
NAME	= minishell

# Compiler and Flags
CC		= 	cc
RM 		= 	rm -f
CFLAGS 	= 	-Wall -Wextra -Werror -g -Iinclude

# Directories
SRCS_DIR				=	srcs/
OBJS_DIR				=	objs/
LIBFT					=	./libft/libft.a
MAIN_DIR				=	$(SRCS_DIR)main/
MINILIB_DIR				=	$(SRCS_DIR)minilib/
INIT_DIR				=	$(MINILIB_DIR)init/
FREE_DIR				=	$(MINILIB_DIR)free/
PARS_DIR				=	$(MINILIB_DIR)parsing/
ENV_DIR					=	$(MINILIB_DIR)env/
PATH_DIR				=	$(MINILIB_DIR)path/
EXEC_ONE_CMD_DIR		=	$(MINILIB_DIR)execution_one_cmd/
COMMANDS_DIR			=	$(MINILIB_DIR)commands/
REDIR_DIR				=	$(MINILIB_DIR)redirections/
BUILTIN_DIR				=	$(MINILIB_DIR)builtin/
HEREDOC_DIR				= 	$(MINILIB_DIR)heredoc/
TOKENIZE_PARS_DIR 		=	$(PARS_DIR)tokenize/
HANDLE_DIR		 		=	$(TOKENIZE_PARS_DIR)handle/

# Source Files

#	src/
#	|-second/
#	|-third/

INIT_SRC	=	$(INIT_DIR)init.c\
				$(INIT_DIR)init_shell.c\
				$(INIT_DIR)init_env.c\
				$(INIT_DIR)init_commands.c\
				$(INIT_DIR)init_normal_token.c\

FREE_SRC	=	$(FREE_DIR)ft_exit.c\
				$(FREE_DIR)free_env.c\
				$(FREE_DIR)free_2d.c\
				$(FREE_DIR)free_tokens.c\
				$(FREE_DIR)free_token.c\
				$(FREE_DIR)free_commands.c\
				$(FREE_DIR)free_file_list.c\
				$(FREE_DIR)check_to_free.c\

ENV_SRC		=	$(ENV_DIR)export_builtin.c\
				$(ENV_DIR)env_builtin.c\
				$(ENV_DIR)print_sorted_env.c\
				$(ENV_DIR)unset_builtin.c\
				$(ENV_DIR)expand_tokens.c\
				$(ENV_DIR)expand_variable.c\
				$(ENV_DIR)extract_literal.c\
				$(ENV_DIR)handle_dollar.c\
				$(ENV_DIR)extract_var_value.c\
				$(ENV_DIR)get_env_value.c\
				$(ENV_DIR)append_and_free.c\
				$(ENV_DIR)append_result.c\

CMD_PARS_SRC = 	$(PARS_DIR)commands/tokens_to_commands.c\
				$(PARS_DIR)commands/if_outputPipe.c\
				$(PARS_DIR)commands/if_input_filesHeredoc.c\
				$(PARS_DIR)commands/if_output_filesAppend.c\
				$(PARS_DIR)commands/has_more_redirections.c\
				$(PARS_DIR)commands/create_command.c\
				$(PARS_DIR)commands/add_to_list.c\
		
TOKENIZE_PARS_SRC = $(TOKENIZE_PARS_DIR)tokenize_pipe_op.c\
					$(TOKENIZE_PARS_DIR)tokenize_input_redir.c\
					$(TOKENIZE_PARS_DIR)tokenize_output_redir.c\
					$(TOKENIZE_PARS_DIR)tokenize_normal_string.c\
					$(TOKENIZE_PARS_DIR)tokenize_quoted.c\
					$(TOKENIZE_PARS_DIR)get_tokens.c\
					$(TOKENIZE_PARS_DIR)create_quoted_token.c\
					$(TOKENIZE_PARS_DIR)process_token.c\

HANDLE_SRC	=	$(HANDLE_DIR)handle_heredoc_redir.c\
				$(HANDLE_DIR)handle_input_file_redir.c\
				$(HANDLE_DIR)handle_output_file_redir.c\
				$(HANDLE_DIR)handle_output_append_redir.c\
				$(HANDLE_DIR)handle_eof.c\

PARS_SRC	=	$(CMD_PARS_SRC)\
				$(HANDLE_SRC)\
				$(TOKENIZE_PARS_SRC)\
				$(PARS_DIR)count_pipe.c\
				$(PARS_DIR)merge_words.c\
				$(PARS_DIR)merge_two_tokens.c\
				$(PARS_DIR)advance_and_merge.c\
				$(PARS_DIR)read_quoted_content.c\
				$(PARS_DIR)allocate_normal_word.c\

PARS_SRC	=	$(PARS_DIR)get_tokens.c\
				$(PARS_DIR)count_pipe.c\
				$(PARS_DIR)merge_words.c\
				$(PARS_DIR)tokenize_quoted.c\
				$(PARS_DIR)tokenize_pipe_op.c\
				$(PARS_DIR)tokenize_redir_op1.c\
				$(PARS_DIR)tokenize_redir_op2.c\
				$(PARS_DIR)tokenize_normal_string.c\

PATH_SRS	=	$(PATH_DIR)already_path.c\
				$(PATH_DIR)is_executable.c\
				$(PATH_DIR)get_path.c\
				$(PATH_DIR)find_cmd_path.c\
				$(PATH_DIR)find_path.c\
				$(PATH_DIR)join_path.c\

EXEC_ONE_CMD_SRE	=	$(EXEC_ONE_CMD_DIR)env_to_envp.c\
						$(EXEC_ONE_CMD_DIR)exec_command.c\
						$(EXEC_ONE_CMD_DIR)exec_builtin.c\
						$(EXEC_ONE_CMD_DIR)is_builtin.c\

COMMANDS_SRC	=	$(COMMANDS_DIR)tokens_to_commands.c\
					$(COMMANDS_DIR)compare_commands.c\

REDIR_SRC		=	$(REDIR_DIR)handle_empty_cmd.c\
					$(REDIR_DIR)input_redirection.c\
					$(REDIR_DIR)output_redirection.c\
					$(REDIR_DIR)is_file_and_exec.c\
					$(REDIR_DIR)handell_redirection.c \

BUILTIN_SRC		=	$(BUILTIN_DIR)history_builtin.c\
					$(BUILTIN_DIR)pwd_builtin.c\
					$(BUILTIN_DIR)exit_builtin.c\
					$(BUILTIN_DIR)echo_builtin.c\
					$(BUILTIN_DIR)unset_builtin.c\
					$(BUILTIN_DIR)export_builtin.c\
					$(BUILTIN_DIR)cd_builtin.c\

MINILIB_SRC	= 	$(PARS_SRC)\
				$(ENV_SRC)\
				$(INIT_SRC)\
				$(FREE_SRC)\
				$(REDIR_SRC)\
				$(COMMANDS_SRC)\
				$(EXEC_ONE_CMD_SRE)\
				$(PATH_SRS)\
				$(HEREDOC_SRC)\
				$(MINILIB_DIR)signals.c\
				$(BUILTIN_SRC)\

MAIN_SRC =	$(MAIN_DIR)main.c\
			$(MAIN_DIR)main_fork.c\
			$(MAIN_DIR)main_redirection.c
		    $(MAIN_DIR)print_banner.c\
		    $(MAIN_DIR)main_loop.c\
		    $(MAIN_DIR)allocate_argv.c\
		    $(MAIN_DIR)argv_for_commands.c\

SRCS	= $(MAIN_SRC) $(MINILIB_SRC)

OBJS	= $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))


# Build Rules
# start:
# 	make all

all: $(NAME) $(LIBFT)

$(LIBFT):
	@make -s -C ./libft > /dev/null

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline > /dev/null
	@echo "\n[ $(YELLOW)$(NAME) $(RESET)] $(GREEN)has been created!$(RESET)\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
#   @echo "Creating $(YELLOW)$(@D)$(RESET)/ $(GREEN)$(@F)$(RESET)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ > /dev/null

clean:
	@$(RM) -r $(OBJS_DIR)
	@make clean -s -C libft
	@echo "\n$(BLUE)Obj files cleaned.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -s -C libft
	@echo "\n$(BLUE)Binary files cleaned.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
