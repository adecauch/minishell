/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:15:38 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/10 21:29:30 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	minishell(char **envp)
{
	char	*input;

	(void)envp;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("\nexit\n");
			break ;
		}
		else
			add_history(input);
		free(input);
	}
	return (0);
}
