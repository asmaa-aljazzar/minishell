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
PROG_DIR				=	$(SRCS_DIR)prog/
INIT_DIR				=	$(PROG_DIR)init/
FREE_DIR				=	$(PROG_DIR)free/
PARS_DIR				=	$(PROG_DIR)parsing/
BUILTIN_DIR				=	$(PROG_DIR)builtins/
EXPAND_DIR				=	$(PROG_DIR)expand/
LEXER_AND_TOKENIZER_DIR =	$(PROG_DIR)lexer_and_tokenizer/
SIGNALS_DIR				=	$(PROG_DIR)signals/
ERRORS_DIR 				= 	$(PROG_DIR)errors/
DEBUG_DIR				=	$(PROG_DIR)debug/
EXECUTION_DIR			=	$(PROG_DIR)execution/
PIPE_DIR				= 	$(EXECUTION_DIR)pipe/
PATH_DIR				= 	$(EXECUTION_DIR)path/
COMM_DIR				= 	$(EXECUTION_DIR)command/
REDIR_DIR				=	$(EXECUTION_DIR)redirection/
HEREDOC_DIR				= 	$(REDIR_DIR)heredoc/
I_O_A_DIR				= 	$(REDIR_DIR)input_output_append/


# Source Files

#	src/
#	|-second/
#	|-third/

MAIN_SRC 	= 	$(MAIN_DIR)main.c\
			 	$(MAIN_DIR)main_loop.c\
			 	$(MAIN_DIR)main_redirection.c\

MINILIB_SRC	=	$(MINILIB_DIR)is_positive_number.c\
				$(MINILIB_DIR)print_banner.c\
				$(MINILIB_DIR)print_slowly.c\
				$(MINILIB_DIR)handle_eof.c\
				$(MINILIB_DIR)is_builtin.c\
				$(MINILIB_DIR)update_glued.c\
				$(MINILIB_DIR)count_pipe.c\
				$(MINILIB_DIR)count_max_tokens_after_expansion.c\
				$(MINILIB_DIR)append_result.c\
				$(MINILIB_DIR)append_and_free.c\
				$(MINILIB_DIR)is_whitespace.c\
				$(MINILIB_DIR)count_words_in_string.c\
				$(MINILIB_DIR)split_on_whitespace.c\
				$(MINILIB_DIR)extract_word.c\
				$(MINILIB_DIR)copy_token_to_argvs.c\
				$(MINILIB_DIR)add_to_list.c\
				$(MINILIB_DIR)has_more_redirections.c\
				$(MINILIB_DIR)print_sorted_env.c\

INIT_SRC	=	$(INIT_DIR)init_env.c\
				$(INIT_DIR)init.c\
				$(INIT_DIR)init_shell.c\
				$(INIT_DIR)init_command.c\
				$(INIT_DIR)init_split_array.c\

FREE_SRC	=	$(FREE_DIR)ft_exit.c\
				$(FREE_DIR)free_complex_resources.c\
				$(FREE_DIR)free_simple_resources.c\
				$(FREE_DIR)free_commands.c\
				$(FREE_DIR)check_to_free.c\
				$(FREE_DIR)free_2d.c\
				$(FREE_DIR)free_tokens.c\
				$(FREE_DIR)free_token.c\
				$(FREE_DIR)free_env.c\
				$(FREE_DIR)free_split_array.c\

PARS_SRC	=	$(PARS_DIR)allocate_commands.c\
				$(PARS_DIR)allocate_argv.c\
				$(PARS_DIR)argv_for_commands.c\
				$(PARS_DIR)fill_argvs.c\
				$(PARS_DIR)process_token_to_fill.c\
				$(PARS_DIR)if_input_filesHeredoc.c\
				$(PARS_DIR)if_output_filesAppend.c\
				$(PARS_DIR)if_outputPipe.c\
				$(PARS_DIR)tokens_to_commands.c\

PIPE_SRC	=	$(PIPE_DIR)pipe.c\

PATH_SRC =	$(PATH_DIR)already_path.c\
			$(PATH_DIR)find_cmd_path.c\
			$(PATH_DIR)find_path.c\
			$(PATH_DIR)get_path.c\
			$(PATH_DIR)is_executable.c\
			$(PATH_DIR)join_path.c

HEREDOC_SRC =	$(HEREDOC_DIR)append_line_to_content.c\
				$(HEREDOC_DIR)append_single_char.c\
				$(HEREDOC_DIR)append_to_result.c\
				$(HEREDOC_DIR)create_heredoc_pipe.c\
				$(HEREDOC_DIR)expand_env_var.c\
				$(HEREDOC_DIR)expand_exit_code.c\
				$(HEREDOC_DIR)extract_var_name.c\
				$(HEREDOC_DIR)is_delimiter_line.c\
				$(HEREDOC_DIR)print_eof_warning.c\
				$(HEREDOC_DIR)process_all_heredocs.c\
				$(HEREDOC_DIR)process_discarded_heredocs.c\
				$(HEREDOC_DIR)process_final_heredoc.c\
				$(HEREDOC_DIR)process_heredoc_readline.c\
				$(HEREDOC_DIR)read_heredoc_content.c\
				$(HEREDOC_DIR)read_until_delimiter.c\
				$(HEREDOC_DIR)should_expand_heredoc.c\
				$(HEREDOC_DIR)setup_heredoc_input.c\
				$(HEREDOC_DIR)expand_heredoc_variable.c\

I_O_A_SRC	=	$(I_O_A_DIR)handell_redirection.c\
				$(I_O_A_DIR)input_redirection.c\
				$(I_O_A_DIR)output_redirection.c\

REDIR_SRC	=	$(HEREDOC_SRC)\
				$(I_O_A_SRC)

COMM_SRC	=	$(COMM_DIR)compare_commands.c\
				$(COMM_DIR)exec_builtin.c\
				$(COMM_DIR)exec_command.c\
				$(COMM_DIR)execute_single_command.c\
				$(COMM_DIR)execute_external.c\

EXECUTION_SRC	=	$(PIPE_SRC)\
					$(PATH_SRC)\
					$(COMM_SRC)\
					$(REDIR_SRC)\

EXPAND_SRC	=	$(EXPAND_DIR)append_env_node.c\
				$(EXPAND_DIR)create_env_node.c\
				$(EXPAND_DIR)get_env_value.c\
				$(EXPAND_DIR)increase_SHLVL_var.c\
				$(EXPAND_DIR)update_env_var.c\
				$(EXPAND_DIR)create_new_env_var.c\
				$(EXPAND_DIR)update_existing_env_var.c\
				$(EXPAND_DIR)update_envp_array.c\
				$(EXPAND_DIR)append_envp.c\
				$(EXPAND_DIR)build_envp_entry.c\
				$(EXPAND_DIR)replace_existing_envp.c\
				$(EXPAND_DIR)expand_and_split_token.c\
				$(EXPAND_DIR)expand_tokens.c\
				$(EXPAND_DIR)handle_double_quoted_token.c\
				$(EXPAND_DIR)handle_single_quoted_token.c\
				$(EXPAND_DIR)handle_unquoted_token.c\
				$(EXPAND_DIR)handle_first_split_token.c\
				$(EXPAND_DIR)handle_empty_expansion.c\
				$(EXPAND_DIR)handle_dollar.c\
				$(EXPAND_DIR)extract_var_value.c\
				$(EXPAND_DIR)extract_literal.c\
				$(EXPAND_DIR)expand_variable.c\

BUILTIN_SRC = 	$(BUILTIN_DIR)cd_builtin.c\
				$(BUILTIN_DIR)echo_builtin.c\
				$(BUILTIN_DIR)env_builtin.c\
				$(BUILTIN_DIR)exit_builtin.c\
				$(BUILTIN_DIR)export_builtin.c\
				$(BUILTIN_DIR)pwd_builtin.c\
				$(BUILTIN_DIR)unset_builtin.c

LEXER_AND_TOKENIZER_SRC = 	$(LEXER_AND_TOKENIZER_DIR)get_tokens.c\
						 	$(LEXER_AND_TOKENIZER_DIR)process_token.c\
						 	$(LEXER_AND_TOKENIZER_DIR)select_tokenizer.c\
						 	$(LEXER_AND_TOKENIZER_DIR)tokenize_pipe_op.c\
						 	$(LEXER_AND_TOKENIZER_DIR)tokenize_input_redir.c\
						 	$(LEXER_AND_TOKENIZER_DIR)handle_heredoc_redir.c\
						 	$(LEXER_AND_TOKENIZER_DIR)handle_input_file_redir.c\
						 	$(LEXER_AND_TOKENIZER_DIR)tokenize_output_redir.c\
						 	$(LEXER_AND_TOKENIZER_DIR)handle_output_append_redir.c\
						 	$(LEXER_AND_TOKENIZER_DIR)handle_output_file_redir.c\
						 	$(LEXER_AND_TOKENIZER_DIR)tokenize_quoted.c\
						 	$(LEXER_AND_TOKENIZER_DIR)read_quoted_content.c\
						 	$(LEXER_AND_TOKENIZER_DIR)create_quoted_token.c\
						 	$(LEXER_AND_TOKENIZER_DIR)tokenize_normal_string.c\
						 	$(LEXER_AND_TOKENIZER_DIR)allocate_normal_word.c\
						 	$(LEXER_AND_TOKENIZER_DIR)fill_normal_token.c\
						 	$(LEXER_AND_TOKENIZER_DIR)create_new_token.c\
						 	$(LEXER_AND_TOKENIZER_DIR)merge_words.c\
						 	$(LEXER_AND_TOKENIZER_DIR)merge_two_tokens.c\
						 	$(LEXER_AND_TOKENIZER_DIR)advance_and_merge.c\

ERRORS_SRC		=	$(ERRORS_DIR)validate_syntax.c\
					$(ERRORS_DIR)check_redirection_syntax.c\
					$(ERRORS_DIR)check_pipe_syntax.c\

SIGNALS_SRC 	=	$(SIGNALS_DIR)setup_signals_child.c\
					$(SIGNALS_DIR)setup_signals_parent.c\
					$(SIGNALS_DIR)setup_signals_execution.c\
					$(SIGNALS_DIR)setup_signals_heredoc.c\
					$(SIGNALS_DIR)setup_signals_readline.c\
					$(SIGNALS_DIR)sigint_handler.c\

DEBUG_SRC = $(DEBUG_DIR)debug_print_envp_array.c\
			$(DEBUG_DIR)debug_print_env_list.c\
			$(DEBUG_DIR)debug_print_tokens.c\
			$(DEBUG_DIR)debug_command.c\



# PARS_DIR	= 	$(PARS)parse_and_execute.c

PROG_SRC	=	$(INIT_SRC)\
				$(EXPAND_SRC)\
 				$(FREE_SRC)\
 				$(PARS_SRC)\
 				$(BUILTIN_SRC)\
 				$(EXECUTION_SRC)\
 				$(LEXER_AND_TOKENIZER_SRC)\
 				$(ERRORS_SRC)\
				$(SIGNALS_SRC)\
				$(DEBUG_SRC)\

SRCS	=	$(MAIN_SRC)\
			$(MINILIB_SRC)\
			$(PROG_SRC)\
			

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
