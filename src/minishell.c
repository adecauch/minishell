/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:15:38 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 17:22:35 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_input(t_shell *shell)
{
	shell->head = tokenizer(shell->input);
	//print_token_list(shell->head);
	shell->root = make_ast(shell->head, shell->envp, shell->last_status);
	//print_ast(shell->root);
	shell->last_status = exec_ast(shell);
	free_token_list(shell->head);
	free_cmd_list(shell->root);
	return (shell->last_status);
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
		shell.last_status = process_input(&shell);
		free(shell.input);
		if (shell.exit)
		{
			shell.exit = 0;
			break;
		}
	}
	return (shell.last_status);
}
