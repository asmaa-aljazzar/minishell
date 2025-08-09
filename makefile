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
INIT_DIR				=	$(SRCS_DIR)init/
FREE_DIR				=	$(SRCS_DIR)free/
PARS_DIR				=	$(SRCS_DIR)parsing/
BUILTINS_DIR			=	$(SRCS_DIR)builtins/
EXPAND_DIR				=	$(SRCS_DIR)expand/
LEXER_AND_TOKENIZE_DIR 	=	$(SRCS_DIR)tokenize/
SIGNALS_DIR				=	$(SRCS_DIR)signals/
ERRORS_DIR				=	$(SRCS_DIR)erorrs/



HEREDOC_DIR				= 	$(MINILIB_DIR)heredoc/
PIPE_DIR				= 	$(MINILIB_DIR)pipe/
REDIR_DIR				=	$(MINILIB_DIR)redirections/
PATH_DIR				=	$(MINILIB_DIR)path/
EXECUTION_DIR			=	$(MINILIB_DIR)exec_one_cmd/
HANDLE_DIR		 		=	$(LEXER_AND_TOKENIZE_DIR)handle/

# Source Files

#	src/
#	|-second/
#	|-third/

MAIN_SRC 	= 	$(MAIN_DIR)main.c\

MINILIB_SRC	=	$(MINILIB_DIR)is_positive_number.c\

INIT_SRC	=	$(INIT_DIR)init_env.c\
				$(INIT_DIR)init.c\

FREE_SRC	=	$(FREE_DIR)ft_exit.c\
				$(FREE_DIR)free_complex_resources.c\
				$(FREE_DIR)free_simple_resources.c\
				$(FREE_DIR)free_commands.c\
				$(FREE_DIR)free_2d.c\
				$(FREE_DIR)free_tokens.c\
				$(FREE_DIR)free_env.c\

PARS_SRC	=	

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

BUILTINS_SRC	=	

LEXER_AND_TOKENIZE_SRC = 	

ERRORS_SRC		=	

SIGNALS_SRC =

DEBUG_SRC = $(DEBUG_DIR)debug_print_envp_array.c\
			$(DEBUG_DIR)debug_print_env_list.c\



# PARS_DIR	= 	$(PARS)parse_and_execute.c


SRCS	=	$(MAIN_SRC)\
			$(MINILIB_SRC)\
			$(INIT_SRC)\
			$(EXPAND_SRC)\
 			$(FREE_SRC)\
 			$(PARS_SRC)\
 			$(BUILTINS_SRC)\
 			$(LEXER_AND_TOKENIZE_SRC)\
 			$(ERRORS_SRC)\
			$(SIGNALS_SRC)\
			$(DEBUG_SRC)\

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
