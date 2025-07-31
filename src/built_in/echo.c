/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:29:05 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/31 15:46:09 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	check_arg(char **cmd_args, int *i)
{
	while (check_n(cmd_args[*i]))
		(*i)++;
	return (check_n(cmd_args[1]));
}

int	bi_echo(char **cmd_args)
{
	int		i;
	bool	n;

	i = 1;
	n = check_arg(cmd_args, &i);
	while (cmd_args[i])
	{
		printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}
