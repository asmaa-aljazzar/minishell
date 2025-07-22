# Library Name
NAME    =	libft.a

# Compiler and Flags
CC      =	cc
CFLAGS  =	-Wall -Wextra -Werror -g -Iinclude
AR		=	ar rcs
RM		=	rm -f

# Directories
SRC_DIR	=	src/
OBJ_DIR =	obj/

# Source files

FT_IS_DIR	= 	$(SRC_DIR)ft_is/ft_isalnum.c\
				$(SRC_DIR)ft_is/ft_isalpha.c\
				$(SRC_DIR)ft_is/ft_isascii.c\
				$(SRC_DIR)ft_is/ft_isdigit.c\
				$(SRC_DIR)ft_is/ft_isprint.c\
				$(SRC_DIR)ft_is/ft_isdelim.c

FT_LST_DIR	= 	$(SRC_DIR)ft_lst/ft_lstadd_back.c\
				$(SRC_DIR)ft_lst/ft_lstadd_front.c\
				$(SRC_DIR)ft_lst/ft_lstclear.c\
				$(SRC_DIR)ft_lst/ft_lstdelone.c\
				$(SRC_DIR)ft_lst/ft_lstiter.c\
				$(SRC_DIR)ft_lst/ft_lstlast.c\
				$(SRC_DIR)ft_lst/ft_lstmap.c\
				$(SRC_DIR)ft_lst/ft_lstnew.c\
				$(SRC_DIR)ft_lst/ft_lstsize.c

FT_MEM_DIR	= 	$(SRC_DIR)ft_mem/ft_bzero.c\
				$(SRC_DIR)ft_mem/ft_calloc.c\
				$(SRC_DIR)ft_mem/ft_memchr.c\
				$(SRC_DIR)ft_mem/ft_memcmp.c\
				$(SRC_DIR)ft_mem/ft_memcpy.c\
				$(SRC_DIR)ft_mem/ft_memmove.c\
				$(SRC_DIR)ft_mem/ft_memset.c

FT_PUT_DIR	=	$(SRC_DIR)ft_put/ft_putchar_fd.c\
				$(SRC_DIR)ft_put/ft_putendl_fd.c\
				$(SRC_DIR)ft_put/ft_putnbr_fd.c\
				$(SRC_DIR)ft_put/ft_putstr_fd.c

FT_STR_DIR	=	$(SRC_DIR)ft_str/ft_split.c\
				$(SRC_DIR)ft_str/ft_strchr.c\
				$(SRC_DIR)ft_str/ft_strdup.c\
				$(SRC_DIR)ft_str/ft_striteri.c\
				$(SRC_DIR)ft_str/ft_strjoin.c\
				$(SRC_DIR)ft_str/ft_strlcat.c\
				$(SRC_DIR)ft_str/ft_strlcpy.c\
				$(SRC_DIR)ft_str/ft_strlen.c\
				$(SRC_DIR)ft_str/ft_strmapi.c\
				$(SRC_DIR)ft_str/ft_strncmp.c\
				$(SRC_DIR)ft_str/ft_strnstr.c\
				$(SRC_DIR)ft_str/ft_strrchr.c\
				$(SRC_DIR)ft_str/ft_strtrim.c\
				$(SRC_DIR)ft_str/ft_substr.c

FT_TO_DIR	=	$(SRC_DIR)ft_to/ft_atoi.c\
				$(SRC_DIR)ft_to/ft_itoa.c\
				$(SRC_DIR)ft_to/ft_tolower.c\
				$(SRC_DIR)ft_to/ft_toupper.c

FT_PRINTF_UTIL_DIR		=	ft_printf_util

FT_PRINTF_DIR	=	$(SRC_DIR)printf/$(FT_PRINTF_UTIL_DIR)/ft_char_format.c\
					$(SRC_DIR)printf/$(FT_PRINTF_UTIL_DIR)/ft_ptr_format.c\
					$(SRC_DIR)printf/$(FT_PRINTF_UTIL_DIR)/ft_decimal_format.c\
					$(SRC_DIR)printf/$(FT_PRINTF_UTIL_DIR)/ft_hex_format.c\
					$(SRC_DIR)printf/$(FT_PRINTF_UTIL_DIR)/ft_str_format.c\
					$(SRC_DIR)printf/$(FT_PRINTF_UTIL_DIR)/ft_unsigned_format.c\
					$(SRC_DIR)printf/ft_format.c\
					$(SRC_DIR)printf/ft_printf.c

SRCS 	=			$(FT_IS_DIR) $(FT_LST_DIR) $(FT_MEM_DIR) $(FT_PUT_DIR) $(FT_STR_DIR) $(FT_TO_DIR) $(FT_PRINTF_DIR)

OBJ		=			$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
# 		patsubst (pattern, replacement, text)
#		For each file in $(SRCS), patsubst does the following:
#			---->	Matches $(SRC_DIR)%.c in the file's path.
# 			---->	Replaces it with $(OBJ_DIR)%.o.

# Build Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
#	@echo "Creating $(@D)/ $(@F)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
# 	-p: Ensures that:
# 		---->	Parent directories are created if they don't exist.
# 		---->	It doesn't throw an error if the directory already exists.
# 	$(@D):
# 		---->	$@: Refers to the target of the current rule (e.g., the file being generated).
# 		---->	$(@D): Extracts the directory part of $@.

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) .cache_exists
#	.cache_exists:
#		---->	This is the specific file being removed.
#		---->	It could be used as a marker or a temporary file in the build process.


fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# ---------------------------------------------------------------------------------------------
#	Old Makefile
# ---------------------------------------------------------------------------------------------

# Libft Source Files
# LIBFT_SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
# 	ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
# 	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
# 	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
# 	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
# 	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

# ft_printf Source Files
# PRINTF_DIR = printf
# PRINTF_UTIL_DIR = $(PRINTF_DIR)/ft_printf_util


# PRINTF_SRCS = $(PRINTF_DIR)/ft_printf.c $(PRINTF_DIR)/ft_format.c
# PRINTF_UTIL_SRCS = $(PRINTF_UTIL_DIR)/ft_char_format.c $(PRINTF_UTIL_DIR)/ft_str_format.c \
# 	$(PRINTF_UTIL_DIR)/ft_decimal_format.c $(PRINTF_UTIL_DIR)/ft_unsigned_format.c \
# 	$(PRINTF_UTIL_DIR)/ft_ptr_format.c $(PRINTF_UTIL_DIR)/ft_hex_format.c

# # Object Files
# LIBFT_OBJ = $(LIBFT_SRCS:%.c=%.o)
# PRINTF_OBJS = $(PRINTF_SRCS:$(PRINTF_DIR)/%.c=$(PRINTF_DIR)/%.o)
# PRINTF_UTIL_OBJS = $(PRINTF_UTIL_SRCS:$(PRINTF_UTIL_DIR)/%.c=$(PRINTF_UTIL_DIR)/%.o
# # Default Rule
# all: $(NAME)

# # Create the Library
# $(NAME): $(LIBFT_OBJ) $(PRINTF_OBJS) $(PRINTF_UTIL_OBJS)
# 	ar rcs $(NAME) $(LIBFT_OBJ) $(PRINTF_OBJS) $(PRINTF_UTIL_OBJS)
# 	@echo "Library $(NAME) created successfully!"

# Compile Source Files into Object Files
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Cleaning Rules
# clean:
# 	rm -f $(LIBFT_OBJ) $(PRINTF_OBJS) $(PRINTF_UTIL_OBJS)
# 	@echo "Object files cleaned!"

# fclean: clean
# 	rm -f $(NAME)
# 	@echo "Library $(NAME) removed!"

# re: fclean all

# # Phony Targets
# .PHONY: all clean fclean re
