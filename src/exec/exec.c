/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:51:17 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 17:44:28 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_single_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	int		original_fds[2];

	cmd = shell->root;
	if (!cmd->cmd_args || !cmd->cmd_args[0])
		return (0);
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	if (exec_redir(cmd->redir) == -1)
	{
		close(original_fds[0]);
		close(original_fds[1]);
		return (1);
	}
	if (cmd->is_builtin)
		return (handle_builtin_exec(cmd, shell, original_fds[0],
				original_fds[1]));
	return (handle_external_cmd(cmd, shell, original_fds[0], original_fds[1]));
}

int	exec_pipeline(t_shell *shell)
{
	t_cmd	*current;
	int		*pipes;
	int		cmd_count;
	int		cmd_index;
	int		*pids;
	int		status;
	int		last_status;

	cmd_count = count_cmds(shell->root);
	if (cmd_count < 2)
		return (0);
	if (create_pipes(&pipes, cmd_count) == -1)
		return (1);
	pids = malloc(sizeof(int) * cmd_count);
	if (!pids)
		return (free(pipes), 1);
	current = shell->root;
	cmd_index = 0;
	while (current && cmd_index < cmd_count)
	{
		pids[cmd_index] = execute_cmd_in_pipeline(current, shell, pipes,
				cmd_index, cmd_count);
		if (pids[cmd_index] == -1)
		{
			close_all_pipes(pipes, cmd_count);
			free(pipes);
			free(pids);
			return (1);
		}
		current = current->next;
		cmd_index++;
	}
	close_all_pipes(pipes, cmd_count);
	free(pipes);
	last_status = 0;
	cmd_index = 0;
	while (cmd_index < cmd_count)
	{
		waitpid(pids[cmd_index], &status, 0);
		if (cmd_index == cmd_count - 1)
			last_status = WEXITSTATUS(status);
		cmd_index++;
	}
	free(pids);
	return (last_status);
}

int	exec_ast(t_shell *shell)
{
	if (!shell->root)
		return (0);
	if (!shell->root->next)
		return (exec_single_cmd(shell));
	return (exec_pipeline(shell));
}
