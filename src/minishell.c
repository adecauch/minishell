/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:15:38 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/08 18:25:30 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(t_shell shell)
{
	shell.head = tokenizer(shell.input);
	print_token_list(shell.head);
	shell.root = make_ast(shell.head, shell.envp, shell.last_status);
	print_ast(shell.root);
	free_token_list(shell.head);
	free_cmd_list(shell.root);
}

int	minishell(t_shell shell)
{
	init_signals();
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
		{
			printf("exit\n");
			break ;
		}
		if (*shell.input)
			add_history(shell.input);
		process_input(shell);
		free(shell.input);
	}
	return (0);
}
