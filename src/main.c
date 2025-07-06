/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:50:33 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/24 03:34:05 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_ast(t_ast *root, char **envp)
{
	(void)root;
	(void)envp;
	printf("AST plus qu'a faire l'ast\n");
}

void	handle_tokenizer_error(t_tokr *tokenizer_result, char *input)
{
	printf("minishell: syntax error near unexpected token `%s'\n",
		tokenizer_result->error_msg);
	free_tokenizer_result(tokenizer_result);
	add_history(input);
	free(input);
}

void	process_input(char *input, char **envp)
{
	t_tokr *tokenizer_result;
	t_ast *root;

	tokenizer_result = tokenizer(input);
	if (!tokenizer_result)
	{
		add_history(input);
		free(input);
		return ;
	}
	if (tokenizer_result->error_msg)
	{
		handle_tokenizer_error(tokenizer_result, input);
		return ;
	}
	root = parse(tokenizer_result->tokens);
	free_tokenizer_result(tokenizer_result);
	if (root)
	{
		expand_ast_variables(root, envp);
		print_ast(root);
		exec_ast(root, envp);
		free_ast(root);
	}
	add_history(input);
	free(input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		process_input(input, envp);
	}
	return (0);
}
