/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:50:33 by adecauch          #+#    #+#             */
/*   Updated: 2025/05/27 20:33:36 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char    *input;

	while (1)
    {
		input = readline("minishell> ");
        if (!input)
        {
			printf("exit\n");
			break;
		}
		add_history(input);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
