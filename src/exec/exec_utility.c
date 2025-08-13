/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:44:50 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/12 22:50:01 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_not_found(char *cmd)
{
	printf("minishell: %s: command not found\n", cmd);
	return (127);
}

int	handle_builtin_exec(t_cmd *cmd, t_shell *shell, int stdin_fd, int stdout_fd)
{
	int	status;

	status = exec_builtin(cmd, shell);
	dup2(stdout_fd, STDOUT_FILENO);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	close(stdout_fd);
	return (status);
}

void	restore_fds_and_close(int stdin_fd, int stdout_fd)
{
	dup2(stdout_fd, STDOUT_FILENO);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	close(stdout_fd);
}

int	handle_external_cmd(t_cmd *cmd, t_shell *shell, int stdin_fd, int stdout_fd)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_cmd_path(cmd->cmd_args[0], shell->envp);
	if (!cmd_path)
	{
		restore_fds_and_close(stdin_fd, stdout_fd);
		return (command_not_found(cmd->cmd_args[0]));
	}
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, cmd->cmd_args, shell->envp);
		perror("execve failed");
		free(cmd_path);
		exit(127);
	}
	free(cmd_path);
	if (pid > 0)
		waitpid(pid, &status, 0);
	restore_fds_and_close(stdin_fd, stdout_fd);
	return (WEXITSTATUS(status));
}
