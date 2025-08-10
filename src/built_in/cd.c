/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:16:13 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/10 18:48:14 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(char ***envp, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	set_env_var(envp, "OLDPWD", old_pwd);
	set_env_var(envp, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
}

static char	*get_home(char **envp)
{
	int		i;
	char	*home;

	i = find_env_var(envp, "HOME");
	if (i == -1)
		return (NULL);
	return (ft_strchr(envp[i], '=') + 1);
}

int	bi_cd(char **cmd_args, char ***envp)
{
	char	*target_dir;
	char	*old_pwd;

	if (cmd_args[2])
		return (printf("minishell: cd: too many arguments\n"), 2);
	if (!cmd_args[1])
		target_dir = get_home(*envp);
	else
		target_dir = cmd_args[1];
	if (!target_dir)
		return (printf("minishell: cd: HOME not set\n"), 1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target_dir) == -1)
		return (printf("minishell: cd: chdir error\n"), free(old_pwd), 1);
	return (update_pwd(envp, old_pwd), 0);
}
