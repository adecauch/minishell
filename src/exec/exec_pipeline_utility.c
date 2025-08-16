/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utility.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:00:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 17:59:04 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_current_cmd_redir(t_cmd *current_cmd, t_redir *target_redir)
{
	t_redir	*current_redir;

	current_redir = current_cmd->redir;
	while (current_redir && current_redir != target_redir)
		current_redir = current_redir->next;
	return (current_redir != NULL);
}

void	close_unused_heredoc_fds(t_cmd *all_cmds, t_cmd *current_cmd)
{
	t_redir	*redir;

	while (all_cmds)
	{
		redir = all_cmds->redir;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->heredoc_fd != -1)
			{
				if (!is_current_cmd_redir(current_cmd, redir))
				{
					close(redir->heredoc_fd);
					redir->heredoc_fd = -1;
				}
			}
			redir = redir->next;
		}
		all_cmds = all_cmds->next;
	}
}

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
