/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:15:38 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/13 18:09:28 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process_input(char *input, char **envp)
{
	t_token	*head;

	(void)envp;
	if (check_unclosed_quotes(input))
	{
		printf("minishell: unexpected EOF while looking for matching quote\n");
		return ;
	}
	head = tokenizer(input);
	validate_token_list(head);
	if (!check_token_list(head))
		print_token_list(head);
	free_token_list(head);
}

int	minishell(char **envp)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("\nexit\n");
			break ;
		}
		if (*input)
			add_history(input);
		process_input(input, envp);
		free(input);
	}
	return (0);
}
