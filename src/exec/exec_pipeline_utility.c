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
