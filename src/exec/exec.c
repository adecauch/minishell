/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:51:17 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/11 05:17:39 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(char *path_env)
{
	char	**paths;
	int		count;
	int		i, j, start;

	if (!path_env)
		return (NULL);
	count = 1;
	i = 0;
	while (path_env[i])
		if (path_env[i++] == ':')
			count++;
	paths = malloc(sizeof(char *) * (count + 1));
	if (!paths)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':')
		{
			paths[j] = ft_substr(path_env, start, i - start);
			j++;
			start = i + 1;
		}
		i++;
	}
	paths[j] = ft_substr(path_env, start, i - start);
	paths[j + 1] = NULL;
	return (paths);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value("PATH", envp, 0);
	if (!path_env)
		return (NULL);
	paths = split_path(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp)
		{
			full_path = ft_strjoin(tmp, cmd);
			free(tmp);
			if (full_path && access(full_path, F_OK | X_OK) == 0)
			{
				free_str_array(paths);
				return (full_path);
			}
			free(full_path);
		}
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

int	command_not_found(char *cmd)
{
	printf("minishell: %s: command not found\n", cmd);
	return (127);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->cmd_args[0], "echo", 5) == 0)
		return (bi_echo(cmd->cmd_args));
	if (ft_strncmp(cmd->cmd_args[0], "cd", 3) == 0)
		return (bi_cd(cmd->cmd_args, &shell->envp));
	if (ft_strncmp(cmd->cmd_args[0], "pwd", 4) == 0)
		return (bi_pwd(cmd->cmd_args));
	if (ft_strncmp(cmd->cmd_args[0], "export", 7) == 0)
		return (bi_export(cmd->cmd_args, &shell->envp));
	if (ft_strncmp(cmd->cmd_args[0], "unset", 6) == 0)
		return (bi_unset(cmd->cmd_args, &shell->envp));
	if (ft_strncmp(cmd->cmd_args[0], "env", 4) == 0)
		return (bi_env(cmd->cmd_args, shell->envp));
	if (ft_strncmp(cmd->cmd_args[0], "exit", 5) == 0)
		return (bi_exit(cmd->cmd_args, &shell->last_status));
	return (127);
}

int	setup_redirections(t_redir *redir)
{
	t_redir	*current;
	int		fd;

	current = redir;
	while (current)
	{
		if (current->type == IN)
		{
			fd = open(current->file, O_RDONLY);
			if (fd == -1)
			{
				perror(current->file);
				return (-1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (current->type == OUT)
		{
			fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(current->file);
				return (-1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (current->type == APPEND)
		{
			fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(current->file);
				return (-1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (current->type == HEREDOC)
		{
			if (setup_heredoc(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	setup_heredoc(t_redir *redir)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, redir->file, ft_strlen(redir->file)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
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

int	exec_single_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd = shell->root;
	if (!cmd->cmd_args || !cmd->cmd_args[0])
		return (0);
	if (setup_redirections(cmd->redir) == -1)
		return (1);
	if (cmd->is_builtin)
		return (exec_builtin(cmd, shell));
	cmd_path = find_cmd_path(cmd->cmd_args[0], shell->envp);
	if (!cmd_path)
		return (command_not_found(cmd->cmd_args[0]));
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
