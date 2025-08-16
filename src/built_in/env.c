/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:46:23 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/16 20:59:40 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_env(char *arg)
{
	if (arg[0] != 'e' || arg[1] != 'n' || arg[2] != 'v' || arg[3])
		return (0);
	return (1);
}

static bool	is_only_env(char **cmd_args, int *arg_index)
{
	while (cmd_args[*arg_index])
	{
		if (!is_env(cmd_args[*arg_index]))
			return (0);
		(*arg_index)++;
	}
	return (1);
}

int	bi_env(char **cmd_args, char **envp)
{
	int	i;
	int	arg_index;

	arg_index = 1;
	if (!is_only_env(cmd_args, &arg_index))
	{
		printf("env: `%s': No such file or directory\n", cmd_args[arg_index]);
		return (127);
	}
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
