/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:04:02 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/10 17:29:32 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier(char *arg)
{
	char	*name;
	char	*equal_pos;
	int		i;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		name = ft_substr(arg, 0, equal_pos - arg);
		if (!name)
			return (0);
	}
	else
		name = ft_strdup(arg);
	if (!name || !name[0])
		return (free(name), 0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (free(name), 0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (free(name), 0);
		i++;
	}
	free(name);
	return (1);
}

static char	*extract_name(char *arg)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		return (ft_substr(arg, 0, equal_pos - arg));
	else
		return (ft_strdup(arg));
}

static char	*extract_value(char *arg)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		return (ft_strdup(equal_pos + 1));
	else
		return (NULL);
}

int	bi_export(char **cmd_args, char ***envp)
{
	int		i;
	char	*name;
	char	*value;

	if (!cmd_args[1])
		return (print_export(*envp), 0);
	i = 1;
	while (cmd_args[i])
	{
		if (!is_valid_identifier(cmd_args[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				cmd_args[i]);
			return (1);
		}
		name = extract_name(cmd_args[i]);
		value = extract_value(cmd_args[i]);
		set_env_var(envp, name, value);
		free(name);
		if (value)
			free(value);
		i++;
	}
	return (0);
}
