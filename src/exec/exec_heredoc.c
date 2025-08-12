/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:53:08 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/12 23:53:11 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_heredoc(t_redir *redir)
{
	char	*line;
	char	*content;
	char	*temp;

	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, redir->file, ft_strlen(redir->file)) == 0)
		{
			free(line);
			break ;
		}
		temp = content;
		content = ft_strjoin(content, line);
		free(temp);
		temp = content;
		content = ft_strjoin(content, "\n");
		free(temp);
		free(line);
	}
	return (content);
}

static char	*g_last_heredoc_content = NULL;

int	setup_heredoc(t_redir *redir)
{
	int	pipe_fd[2];

	(void)redir;
	if (!g_last_heredoc_content)
		return (0);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	write(pipe_fd[1], g_last_heredoc_content, ft_strlen(g_last_heredoc_content));
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	free(g_last_heredoc_content);
	g_last_heredoc_content = NULL;
	return (0);
}

int	handle_all_heredocs(t_redir *redir)
{
	t_redir	*current;
	t_redir	*last_heredoc;
	char	*content;

	current = redir;
	last_heredoc = NULL;
	while (current)
	{
		if (current->type == HEREDOC)
			last_heredoc = current;
		current = current->next;
	}
	current = redir;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			content = fill_heredoc(current);
			if (current == last_heredoc)
				g_last_heredoc_content = content;
			else
				free(content);
		}
		current = current->next;
	}
	return (0);
}