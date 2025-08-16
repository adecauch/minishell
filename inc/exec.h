/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:49:49 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 18:12:59 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_pipeline
{
	t_cmd	*current;
	int		*pipes;
	int		cmd_count;
	int		cmd_index;
	int		*pids;
	int		status;
	int		last_status;
}	t_pipeline;

/*-----exec.c-----*/

int		exec_single_cmd(t_shell *shell);
int		exec_pipeline(t_shell *shell);
int		exec_ast(t_shell *shell);

/*-----exec_utility.c-----*/

int		command_not_found(char *cmd);
int		handle_builtin_exec(t_cmd *cmd, t_shell *shell, int stdin_fd,
			int stdout_fd);
void	restore_fds_and_close(int stdin_fd, int stdout_fd);
int		handle_external_cmd(t_cmd *cmd, t_shell *shell, int stdin_fd,
			int stdout_fd);
int		count_cmds(t_cmd *cmd);

/*-----exec_single_cmd.c-----*/

char	*find_cmd_path(char *cmd, char **envp);
int		exec_builtin(t_cmd *cmd, t_shell *shell);

/*-----exec_pipeline.c-----*/

int		init_pipeline(t_pipeline *p, t_shell *shell);
int		execute_all_cmds(t_pipeline *p, t_shell *shell);
int		wait_all_cmds(t_pipeline *p);
int		exec_pipeline_cmd(t_cmd *cmd, t_shell *shell, t_pipeline *p);

/*-----exec_pipeline_utility.c-----*/

int		create_pipes(int **pipes, int cmd_count);
void	close_unused_heredoc_fds(t_cmd *all_cmds, t_cmd *current_cmd);
void	setup_child_pipes(int *pipes, int cmd_index, int cmd_count);
void	close_all_pipes(int *pipes, int cmd_count);

/*-----exec_redir.c-----*/

int		setup_in(t_redir *redir);
int		setup_out(t_redir *redir);
int		setup_append(t_redir *redir);
int		exec_redir(t_redir *redir);

/*-----exec_heredoc.c-----*/

char	*fill_heredoc(t_redir *redir);
int		setup_heredoc_with_content(char *content);
t_redir	*find_last_heredoc(t_redir *redir);
char	*handle_all_heredocs(t_redir *redir);

/*-----exec_redir_utility.c-----*/

int		create_output_file(t_redir *redir);
int		setup_output_redir(t_redir *redir);
t_redir	*find_last_input(t_redir *redir);
int		handle_input_redir(t_redir *last_input, char *heredoc_content);

#endif
