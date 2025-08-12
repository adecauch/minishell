/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:46:36 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/12 23:14:42 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	exec_redir(t_redir *redir)
{
	t_redir	*current;
	t_redir	*last_input;
	t_redir	*last_output;

	if (handle_all_heredocs(redir) == -1)
		return (-1);
	current = redir;
	last_input = NULL;
	last_output = NULL;
	while (current)
	{
		if (current->type == IN || current->type == HEREDOC)
			last_input = current;
		else if (current->type == OUT || current->type == APPEND)
			last_output = current;
		current = current->next;
	}
	if (last_output)
	{
		if (last_output->type == OUT && setup_out(last_output) == -1)
			return (-1);
		else if (last_output->type == APPEND && setup_append(last_output) == -1)
			return (-1);
	}
	if (last_input && last_input->type == IN)
		return (setup_in(last_input));
	else if (last_input && last_input->type == HEREDOC)
		return (setup_heredoc(last_input));
	return (0);
}
