# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 18:26:06 by aaljazza          #+#    #+#              #
#    Updated: 2025/07/26 03:26:05 by aaljazza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
EXTERNAL_COMM_DIR		=	$(COMMANDS_DIR)external/
REDIR_DIR				=	$(MINILIB_DIR)redirections/

# Source Files

#	src/
#	|-second/
#	|-third/

INIT_SRC	=	$(INIT_DIR)init.c\
				$(INIT_DIR)init_shell.c\
				$(INIT_DIR)init_env.c\
				$(INIT_DIR)init_commands.c\

FREE_SRC	=	$(FREE_DIR)ft_exit.c\
				$(FREE_DIR)free_2d.c\
				$(FREE_DIR)free_env.c\
				$(FREE_DIR)free_tokens.c\
				$(FREE_DIR)free_commands.c\
				$(FREE_DIR)check_to_free.c\

ENV_SRC		=	$(ENV_DIR)export_builtin.c\
				$(ENV_DIR)env_builtin.c\
				$(ENV_DIR)print_sorted_env.c\
				$(ENV_DIR)unset_builtin.c\
				$(ENV_DIR)expand_tokens.c\
				$(ENV_DIR)expand_variable.c\
				$(ENV_DIR)extract_literal.c\

CMD_PARS_SRC = 	$(PARS_DIR)commands/tokens_to_commands.c\
				$(PARS_DIR)commands/if_outputPipe.c\
				$(PARS_DIR)commands/if_input_filesHeredoc.c\
				$(PARS_DIR)commands/if_output_filesAppend.c\
				$(PARS_DIR)commands/has_more_redirections.c\
				$(PARS_DIR)commands/add_to_list.c\

PARS_SRC	=	$(CMD_PARS_SRC)\
				$(PARS_DIR)get_tokens.c\
				$(PARS_DIR)count_pipe.c\
				$(PARS_DIR)merge_words.c\
				$(PARS_DIR)tokenize_quoted.c\
				$(PARS_DIR)tokenize_pipe_op.c\
				$(PARS_DIR)tokenize_redir_op1.c\
				$(PARS_DIR)tokenize_redir_op2.c\
				$(PARS_DIR)tokenize_normal_string.c\


COMMANDS_SRC	=	$(COMMANDS_DIR)commands.c\
					$(COMMANDS_DIR)exit_command.c\
					$(COMMANDS_DIR)call_pwd.c\
					$(COMMANDS_DIR)call_echo.c\
					$(COMMANDS_DIR)compare_commands.c 

REDIR_SRC		=	$(REDIR_DIR)child_re.c\
					$(REDIR_DIR)parent_re.c\
					$(REDIR_DIR)redirection.c\
					$(REDIR_DIR)redir_compare1.c\
					$(REDIR_DIR)redir_compare2.c\

MINILIB_SRC	= 	$(PARS_SRC)\
				$(ENV_SRC)\
				$(INIT_SRC)\
				$(FREE_SRC)\
				$(REDIR_SRC)\
				$(COMMANDS_SRC)\

DEBUG_SRC = $(DEBUG_DIR)debug_Display_t_command.c\

MAIN_SRC = $(MAIN_DIR)main.c\
		   $(MAIN_DIR)main_fork.c\
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
