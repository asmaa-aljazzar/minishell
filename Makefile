
# Color
RESET	=	\033[0m
RED	=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m


# Standard
NAME	= minishell

# Compiler and Flags
CC		= 	cc
CFLAGS 	= 	-Wall -Wextra -Werror -g -I
RM 		= 	rm -f

# Directories
INC			= 	includes/
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/
BUILTIN		=	$(SRCS_DIR)builtins/
EXE			=	$(SRCS_DIR)exec/
PARS		=	$(SRCS_DIR)parser/
SIG			=	$(SRCS_DIR)signals/
LIBFT		=	./libft/libft.a

# Source Files

#	src/
#	|-second/
#	|-third/

SECOND_DIR	= 	$(SRCS_DIR)


THIRD_DIR	= 	$(SRCS_DIR)


SRCS	= $(SRCS_DIR)main.c

OBJS	= $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))


# Build Rules
# start:
# 	make all

all: $(NAME) $(LIBFT)

$(LIBFT):
	make -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "\n[ $(YELLOW)$(NAME) $(RESET)] $(GREEN)has been created!$(RESET)\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "Creating $(YELLOW)$(@D)$(RESET)/ $(GREEN)$(@F)$(RESET)"
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	make clean -C libft
	@echo "\n$(BLUE)Obj files cleaned.$(RESET)\n"

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft
	@echo "\n$(BLUE) Binary files cleaned.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
