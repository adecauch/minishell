/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:49:49 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/11 04:50:36 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/wait.h>
# include <fcntl.h>

int		exec_ast(t_shell *shell);
int		exec_single_cmd(t_shell *shell);
int		exec_pipeline(t_shell *shell);
char	*find_cmd_path(char *cmd, char **envp);
int		command_not_found(char *cmd);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
int		setup_redirections(t_redir *redir);
int		setup_heredoc(t_redir *redir);

#endif
