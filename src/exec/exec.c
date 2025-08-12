/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:51:17 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/12 23:15:34 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_single_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;
	char	*cmd_path;
	int		original_stdin;
	int		original_stdout;

	cmd = shell->root;
	if (!cmd->cmd_args || !cmd->cmd_args[0])
		return (0);
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (exec_redir(cmd->redir) == -1)
	{
		close(original_stdin);
		close(original_stdout);
		return (1);
	}
	if (cmd->is_builtin)
	{
		status = exec_builtin(cmd, shell);
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		close(original_stdout);
		return (status);
	}
	cmd_path = find_cmd_path(cmd->cmd_args[0], shell->envp);
	if (!cmd_path)
	{
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		close(original_stdout);
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
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (WEXITSTATUS(status));
}

int	exec_pipeline(t_shell *shell)
{
	(void)shell;
	printf("exec pipeline a faire\n");
	return (0);
}

int	exec_ast(t_shell *shell)
{
	if (!shell->root)
		return (0);
	if (!shell->root->next)
		return (exec_single_cmd(shell));
	return (exec_pipeline(shell));
}
