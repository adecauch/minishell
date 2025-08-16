/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:04:02 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/16 22:56:29 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier(char *arg)
{
	char	*equal_pos;
	int		i;
	int		len;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		len = equal_pos - arg;
	else
		len = ft_strlen(arg);
	if (len == 0 || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (i < len)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
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

static char	*remove_quotes(char *str)
{
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

static char	*extract_value(char *arg)
{
	char	*equal_pos;
	char	*value;
	char	*cleaned_value;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		value = ft_strdup(equal_pos + 1);
		cleaned_value = remove_quotes(value);
		free(value);
		return (cleaned_value);
	}
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
		if (value)
			set_env_var(envp, name, value);
		free(name);
		if (value)
			free(value);
		i++;
	}
	return (0);
}
