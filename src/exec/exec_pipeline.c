/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:30:25 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 18:00:26 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipeline(t_pipeline *p, t_shell *shell)
{
	p->cmd_count = count_cmds(shell->root);
	if (p->cmd_count < 2)
		return (0);
	if (create_pipes(&p->pipes, p->cmd_count) == -1)
		return (-1);
	p->pids = malloc(sizeof(int) * p->cmd_count);
	if (!p->pids)
		return (free(p->pipes), -1);
	p->current = shell->root;
	p->cmd_index = 0;
	return (1);
}

int	execute_all_cmds(t_pipeline *p, t_shell *shell)
{
	while (p->current && p->cmd_index < p->cmd_count)
	{
		p->pids[p->cmd_index] = exec_pipeline_cmd(p->current, shell, p);
		if (p->pids[p->cmd_index] == -1)
			return (-1);
		p->current = p->current->next;
		p->cmd_index++;
	}
	return (0);
}

int	wait_all_cmds(t_pipeline *p)
{
	p->last_status = 0;
	p->cmd_index = 0;
	while (p->cmd_index < p->cmd_count)
	{
		waitpid(p->pids[p->cmd_index], &p->status, 0);
		if (p->cmd_index == p->cmd_count - 1)
			p->last_status = WEXITSTATUS(p->status);
		p->cmd_index++;
	}
	return (p->last_status);
}

int	exec_pipeline_cmd(t_cmd *cmd, t_shell *shell, t_pipeline *p)
{
	char	*cmd_path;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_pipes(p->pipes, p->cmd_index, p->cmd_count);
		close_all_pipes(p->pipes, p->cmd_count);
		if (exec_redir(cmd->redir) == -1)
			exit(1);
		if (cmd->is_builtin)
			exit(exec_builtin(cmd, shell));
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
	return (pid);
}
