/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:53:08 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 01:26:29 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_heredoc(t_redir *redir)
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

int	setup_heredoc_with_content(char *content)
{
	int	pipe_fd[2];

	if (!content)
		return (0);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	write(pipe_fd[1], content, ft_strlen(content));
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

t_redir	*find_last_heredoc(t_redir *redir)
{
	t_redir	*current;
	t_redir	*last_heredoc;

	current = redir;
	last_heredoc = NULL;
	while (current)
	{
		if (current->type == HEREDOC)
			last_heredoc = current;
		current = current->next;
	}
	return (last_heredoc);
}

static char	*read_from_temp_file(void)
{
	int		fd;
	char	buffer[1024];
	int		bytes;
	char	*content;

	fd = open("/tmp/minishell_heredoc", O_RDONLY);
	bytes = read(fd, buffer, 1023);
	buffer[bytes] = '\0';
	content = ft_strdup(buffer);
	close(fd);
	unlink("/tmp/minishell_heredoc");
	return (content);
}

char	*handle_all_heredocs(t_redir *redir)
{
	t_redir	*current;
	t_redir	*last_heredoc;
	char	*content;
	char	*last_content;

	last_heredoc = find_last_heredoc(redir);
	last_content = NULL;
	current = redir;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (access("/tmp/minishell_heredoc", F_OK) == 0)
				content = read_from_temp_file();
			else
				content = fill_heredoc(current);
			if (current == last_heredoc)
				last_content = content;
			else
				free(content);
		}
		current = current->next;
	}
	return (last_content);
}
