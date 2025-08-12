/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:42:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 00:42:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_output_file(t_redir *redir)
{
	int	fd;

	if (redir->type == OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_output_redir(t_redir *redir)
{
	t_redir	*current;
	t_redir	*last_output;

	current = redir;
	last_output = NULL;
	while (current)
	{
		if (current->type == OUT || current->type == APPEND)
		{
			if (create_output_file(current) == -1)
				return (-1);
			last_output = current;
		}
		current = current->next;
	}
	if (last_output)
	{
		if (last_output->type == OUT)
			return (setup_out(last_output));
		else
			return (setup_append(last_output));
	}
	return (0);
}

t_redir	*find_last_input(t_redir *redir)
{
	t_redir	*current;
	t_redir	*last_input;

	current = redir;
	last_input = NULL;
	while (current)
	{
		if (current->type == IN || current->type == HEREDOC)
			last_input = current;
		current = current->next;
	}
	return (last_input);
}

int	handle_input_redir(t_redir *last_input, char *heredoc_content)
{
	if (last_input && last_input->type == IN)
	{
		free(heredoc_content);
		return (setup_in(last_input));
	}
	else if (last_input && last_input->type == HEREDOC)
	{
		if (setup_heredoc_with_content(heredoc_content) == -1)
		{
			free(heredoc_content);
			return (-1);
		}
		free(heredoc_content);
	}
	else
		free(heredoc_content);
	return (0);
}
