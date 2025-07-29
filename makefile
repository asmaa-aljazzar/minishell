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
DEBUG_DIR				=	$(SRCS_DIR)debug/

SRCS_DIR				=	srcs/
OBJS_DIR				=	objs/
LIBFT					=	./libft/libft.a
MAIN_DIR				=	$(SRCS_DIR)main/
MINILIB_DIR				=	$(SRCS_DIR)minilib/
INIT_DIR				=	$(MINILIB_DIR)init/
FREE_DIR				=	$(MINILIB_DIR)free/
PARS_DIR				=	$(MINILIB_DIR)parsing/
ENV_DIR					=	$(MINILIB_DIR)env/
COMMANDS_DIR			=	$(MINILIB_DIR)commands/
HEREDOC_DIR				= 	$(MINILIB_DIR)heredoc/
EXTERNAL_COMM_DIR		=	$(COMMANDS_DIR)external/
REDIR_DIR				=	$(MINILIB_DIR)redirections/
PATH_DIR				=	$(MINILIB_DIR)path/
EXEC_ONE_CMD_DIR		=	$(MINILIB_DIR)exec_one_cmd/
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
				$(ENV_DIR)update_env_value.c\
				
				

EXEC_ONE_CMD_SRC =	$(EXEC_ONE_CMD_DIR)exec_builtin.c\
					$(EXEC_ONE_CMD_DIR)exec_command.c\
					$(EXEC_ONE_CMD_DIR)is_builtin.c\

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
				$(PATH_SRC)\
				$(EXEC_ONE_CMD_SRC)\
				$(TOKENIZE_PARS_SRC)\
				$(PARS_DIR)count_pipe.c\
				$(PARS_DIR)merge_words.c\
				$(PARS_DIR)merge_two_tokens.c\
				$(PARS_DIR)advance_and_merge.c\
				$(PARS_DIR)read_quoted_content.c\
				$(PARS_DIR)allocate_normal_word.c\



COMMANDS_SRC	=	$(COMMANDS_DIR)cd_builtin.c\
					$(COMMANDS_DIR)exit_builtin.c\
					$(COMMANDS_DIR)pwd_builtin.c\
					$(COMMANDS_DIR)compare_commands.c\
					$(COMMANDS_DIR)echo_builtin.c\
					

REDIR_SRC		=	$(REDIR_DIR)handell_redirection.c\
					$(REDIR_DIR)input_redirection.c\
					$(REDIR_DIR)output_redirection.c\

PATH_SRC		=	$(PATH_DIR)already_path.c\
					$(PATH_DIR)find_cmd_path.c\
					$(PATH_DIR)find_path.c\
					$(PATH_DIR)join_path.c\
					$(PATH_DIR)is_executable.c\
					$(PATH_DIR)get_path.c\

HEREDOC_SRC		=	$(HEREDOC_DIR)heredoc.c\

MINILIB_SRC	= 	$(PARS_SRC)\
				$(ENV_SRC)\
				$(INIT_SRC)\
				$(FREE_SRC)\
				$(REDIR_SRC)\
				$(COMMANDS_SRC)\
				$(MINILIB_DIR)signals.c\
				$(HEREDOC_SRC)\

DEBUG_SRC = $(DEBUG_DIR)debug_Display_t_command.c\
			$(DEBUG_DIR)debug_check_cmd_heredoc.c\

MAIN_SRC = $(MAIN_DIR)main.c\
		   $(MAIN_DIR)main_fork.c\
		   $(MAIN_DIR)main_redirection.c\
		   $(MAIN_DIR)print_banner.c\
		   $(MAIN_DIR)main_loop.c\
		   $(MAIN_DIR)allocate_argv.c\
		   $(MAIN_DIR)argv_for_commands.c\
#          $(MAIN_DIR)compare_input.c\

# PARS_DIR	= 	$(PARS)parse_and_execute.c


SRCS	= $(MAIN_SRC) $(MINILIB_SRC) $(DEBUG_SRC)

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
