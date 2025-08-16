/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:51:17 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/16 22:22:51 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_single_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	int		original_fds[2];

	cmd = shell->root;
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	if (exec_redir(cmd->redir) == -1)
	{
		close(original_fds[0]);
		close(original_fds[1]);
		return (1);
	}
	if (!cmd->cmd_args || !cmd->cmd_args[0])
	{
		dup2(original_fds[0], STDIN_FILENO);
		dup2(original_fds[1], STDOUT_FILENO);
		close(original_fds[0]);
		close(original_fds[1]);
		return (0);
	}
	if (cmd->is_builtin)
		return (handle_builtin_exec(cmd, shell, original_fds[0],
				original_fds[1]));
	return (handle_external_cmd(cmd, shell, original_fds[0], original_fds[1]));
}

int	exec_pipeline(t_shell *shell)
{
	t_pipeline	p;
	int			init_result;

	init_result = init_pipeline(&p, shell);
	if (init_result <= 0)
		return (init_result);
	if (execute_all_cmds(&p, shell) == -1)
	{
		close_all_pipes(p.pipes, p.cmd_count);
		free(p.pipes);
		free(p.pids);
		return (1);
	}
	close_all_pipes(p.pipes, p.cmd_count);
	free(p.pipes);
	p.last_status = wait_all_cmds(&p);
	free(p.pids);
	return (p.last_status);
}

int	exec_ast(t_shell *shell)
{
	if (!shell->root)
		return (shell->last_status);
	if (!shell->root->next)
		return (exec_single_cmd(shell));
	return (exec_pipeline(shell));
}
