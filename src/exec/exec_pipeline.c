/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:30:25 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 17:44:28 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(int **pipes, int cmd_count)
{
	int	i;

	*pipes = malloc(sizeof(int) * (cmd_count - 1) * 2);
	if (!*pipes)
		return (-1);
	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(*pipes + i * 2) == -1)
		{
			while (--i >= 0)
			{
				close((*pipes)[i * 2]);
				close((*pipes)[i * 2 + 1]);
			}
			free(*pipes);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	setup_child_pipes(int *pipes, int cmd_index, int cmd_count)
{
	if (cmd_index > 0)
	{
		dup2(pipes[(cmd_index - 1) * 2], STDIN_FILENO);
	}
	if (cmd_index < cmd_count - 1)
	{
		dup2(pipes[cmd_index * 2 + 1], STDOUT_FILENO);
	}
}

void	close_all_pipes(int *pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < (cmd_count - 1) * 2)
	{
		close(pipes[i]);
		i++;
	}
}

int	execute_cmd_in_pipeline(t_cmd *cmd, t_shell *shell, int *pipes,
	int cmd_index, int cmd_count)
{
	char	*cmd_path;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_pipes(pipes, cmd_index, cmd_count);
		close_all_pipes(pipes, cmd_count);
		if (exec_redir(cmd->redir) == -1)
			exit(1);
		if (cmd->is_builtin)
		{
			exit(exec_builtin(cmd, shell));
		}
		else
		{
			cmd_path = find_cmd_path(cmd->cmd_args[0], shell->envp);
			if (!cmd_path)
			{
				command_not_found(cmd->cmd_args[0]);
				exit(127);
			}
			execve(cmd_path, cmd->cmd_args, shell->envp);
			free(cmd_path);
			exit(127);
		}
	}
	return (pid);
}
