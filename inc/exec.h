/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:49:49 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/12 22:56:54 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/wait.h>
# include <fcntl.h>

/*-----exec.c-----*/

int		exec_single_cmd(t_shell *shell);
int		exec_pipeline(t_shell *shell);
int		exec_ast(t_shell *shell);

/*-----exec_utility.c-----*/

int		command_not_found(char *cmd);

/*-----exec_single_cmd.c-----*/

char	*find_cmd_path(char *cmd, char **envp);
int		exec_builtin(t_cmd *cmd, t_shell *shell);

/*-----exec_pipeline.c-----*/

/*-----exec_redir.c-----*/

//int		exec_redir(t_redir *redir);
int		setup_redirections(t_redir *redir);
//int		setup_in(t_redir *redir);
//int		setup_out(t_redir *redir);
//int		setup_append(t_redir *redir);
int		setup_heredoc(t_redir *redir);

#endif
