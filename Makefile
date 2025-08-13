# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 11:48:05 by adecauch          #+#    #+#              #
#    Updated: 2025/08/12 22:50:01 by adecauch         ###   ########.fr        #
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

# Project name
NAME = minishell

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC = src/main.c \
	  src/minishell.c \
	  src/libft/ft_isdigit.c \
	  src/libft/ft_isalpha.c \
	  src/libft/ft_isalnum.c \
	  src/libft/ft_isspace.c \
	  src/libft/ft_strlen.c \
	  src/libft/ft_strdup.c \
	  src/libft/ft_strchr.c \
	  src/libft/ft_substr.c \
	  src/libft/ft_strjoin.c \
	  src/libft/ft_itoa.c \
	  src/libft/ft_atoi.c \
	  src/libft/ft_strncmp.c \
	  src/libft/ft_strlcpy.c \
	  src/libft/ft_split.c \
	  src/envp/envp.c \
	  src/envp/envp_utility.c \
	  src/envp/set_env_var_utility.c \
	  src/envp/unset_env_var_utility.c \
	  src/signals/signals.c \
	  src/built_in/echo.c \
	  src/built_in/cd.c \
	  src/built_in/pwd.c \
	  src/built_in/export.c \
	  src/built_in/unset.c \
	  src/built_in/env.c \
	  src/built_in/exit.c \
	  src/built_in/print_export.c \
	  src/parsing/token.c \
	  src/parsing/tokenizer.c \
	  src/parsing/tokenizer_utility_one.c \
	  src/parsing/tokenizer_utility_two.c \
	  src/parsing/ast.c \
	  src/parsing/ast_cmd.c \
	  src/parsing/ast_expand.c \
	  src/parsing/ast_redir.c \
	  src/parsing/ast_utility.c \
	  src/exec/exec.c \
	  src/exec/exec_utility.c \
	  src/exec/exec_single_cmd.c \
	  src/exec/exec_pipeline.c \
	  src/exec/exec_redir.c \
	  src/exec/exec_redir_utility.c \
	  src/exec/exec_heredoc.c \
	  src/debug/debug.c

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    RLFLAGS = -lreadline
else ifeq ($(UNAME_S),Darwin)
    RLFLAGS = -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
endif

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(RLFLAGS)
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
