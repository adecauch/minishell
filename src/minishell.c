/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:15:38 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/11 15:42:34 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process_input(char *input, char **envp)
{
	if (check_closed_quotes(input))
	{
		printf("minishell: unexpected E0F while looking for matching quote\n");
		return ;
	}
	(void)envp;
	printf("tokenizer\n");
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
