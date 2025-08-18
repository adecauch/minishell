/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:43:33 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/18 04:25:41 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (cmd);
}

static char	*search_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp)
		{
			full_path = ft_strjoin(tmp, cmd);
			free(tmp);
			if (full_path && access(full_path, F_OK | X_OK) == 0)
			{
				free_str_array(paths);
				return (full_path);
			}
			free(full_path);
		}
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (!cmd)
		return (NULL);
	result = check_absolute_path(cmd);
	if (result != cmd)
		return (result);
	path_env = get_env_value("PATH", envp, 0);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	return (search_in_paths(cmd, paths));
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->cmd_args[0], "echo", 5) == 0)
		return (bi_echo(cmd->cmd_args));
	if (ft_strncmp(cmd->cmd_args[0], "cd", 3) == 0)
		return (bi_cd(cmd->cmd_args, &shell->envp));
	if (ft_strncmp(cmd->cmd_args[0], "pwd", 4) == 0)
		return (bi_pwd(cmd->cmd_args));
	if (ft_strncmp(cmd->cmd_args[0], "export", 7) == 0)
		return (bi_export(cmd->cmd_args, &shell->envp));
	if (ft_strncmp(cmd->cmd_args[0], "unset", 6) == 0)
		return (bi_unset(cmd->cmd_args, &shell->envp));
	if (ft_strncmp(cmd->cmd_args[0], "env", 4) == 0)
		return (bi_env(cmd->cmd_args, shell->envp));
	if (ft_strncmp(cmd->cmd_args[0], "exit", 5) == 0)
		return (bi_exit(cmd->cmd_args, shell->last_status, &shell->exit));
	return (127);
}
