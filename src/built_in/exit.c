/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:12:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 17:18:34 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_numeric_arg(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	bi_exit(char **cmd_args, bool *exit)
{
	printf("exit\n");
	if (!cmd_args[1])
	{
		*exit = 1;
		return (0);
	}
	else if (!is_numeric_arg(cmd_args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd_args[1]);
		*exit = 0;
		return (2);
	}
	else if (cmd_args[2])
	{
		printf("minishell: exit: too many arguments\n");
		*exit = 0;
		return (2);
	}
	else
	{
		*exit = 1;
		return (ft_atoi(cmd_args[1]) % 256);
	}
}
