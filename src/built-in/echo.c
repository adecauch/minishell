/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:16:34 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/09 22:00:20 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_flag(char *flag)
{
	int	i;

	i = 2;
	if (!flag || flag[0] != '-' || flag[1] != 'n')
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **args)
{
	int	i;

	i = 1;
	while (args[i] && check_flag(args[i]))
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!check_flag(args[1]))
		printf("\n");
	return (0);
}
/*
int	main(void)
{
	char *test[] = {
		"echo",
		"-n",
		"-nnnnnnnn",
		"test",
		"test",
		NULL
	};
	builtin_echo(test);
}
*/
//ccf src/built-in/echo.c -o echo
