/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:15:53 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/10 20:20:48 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	bi_unset(char **cmd_args, char ***envp)
{
	int	i;

	if (!cmd_args[1])
		return (0);
	i = 1;
	while (cmd_args[i])
	{
		if (is_valid_identifier_name(cmd_args[i]))
			unset_env_var(envp, cmd_args[i]);
		i++;
	}
	return (0);
}
