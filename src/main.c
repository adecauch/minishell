/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:50:33 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/11 04:00:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	exec_ast(t_ast *root, char **envp)
{
	(void)root;
	(void)envp;
	// TODO: Implement AST execution
	ft_putstr_fd("AST execution not yet implemented\n", 1);
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_ast	*root;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		tokens = tokenizer(input);
		root = parse(tokens);
		free_token_list(tokens);
		ast_print(root, 0);
		exec_ast(root, NULL);
		free_ast(root);
		add_history(input);
		free(input);
	}
	return (0);
}
