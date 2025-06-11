# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 11:48:05 by adecauch          #+#    #+#              #
#    Updated: 2025/06/11 03:56:41 by adecauch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./inc
LDLIBS = -lreadline

# Project name
NAME = minishell

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC = src/main.c \
      src/libft/ft_atoi.c \
      src/libft/ft_bzero.c \
      src/libft/ft_calloc.c \
      src/libft/ft_isalnum.c \
      src/libft/ft_isalpha.c \
      src/libft/ft_isascii.c \
      src/libft/ft_isdigit.c \
      src/libft/ft_isprint.c \
      src/libft/ft_isspace.c \
      src/libft/ft_itoa.c \
      src/libft/ft_lstadd_back_bonus.c \
      src/libft/ft_lstadd_front_bonus.c \
      src/libft/ft_lstclear_bonus.c \
      src/libft/ft_lstdelone_bonus.c \
      src/libft/ft_lstiter_bonus.c \
      src/libft/ft_lstlast_bonus.c \
      src/libft/ft_lstmap_bonus.c \
      src/libft/ft_lstnew_bonus.c \
      src/libft/ft_lstsize_bonus.c \
      src/libft/ft_memchr.c \
      src/libft/ft_memcmp.c \
      src/libft/ft_memcpy.c \
      src/libft/ft_memmove.c \
      src/libft/ft_memset.c \
      src/libft/ft_putchar_fd.c \
      src/libft/ft_putendl_fd.c \
      src/libft/ft_putnbr_fd.c \
      src/libft/ft_putstr_fd.c \
      src/libft/ft_split.c \
      src/libft/ft_strchr.c \
      src/libft/ft_strdup.c \
      src/libft/ft_striteri.c \
      src/libft/ft_strjoin.c \
      src/libft/ft_strlcat.c \
      src/libft/ft_strlcpy.c \
      src/libft/ft_strlen.c \
      src/libft/ft_strmapi.c \
      src/libft/ft_strncmp.c \
      src/libft/ft_strnstr.c \
      src/libft/ft_strrchr.c \
      src/libft/ft_strtrim.c \
      src/libft/ft_substr.c \
      src/libft/ft_tolower.c \
      src/libft/ft_toupper.c \
	  src/tokenizer/tokenizer.c \
	  src/tokenizer/token.c \
	  src/tokenizer/tokenizer_utility.c \
	  src/debug/debug_one.c

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(LDLIBS)
	@echo "$(GREEN)Compilation successful!$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Removed object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Removed executable$(RESET)"

re: fclean all

.PHONY: all clean fclean re
