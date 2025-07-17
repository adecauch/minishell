/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:10 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/17 12:29:19 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_type_redir
{
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	bool			ex_here;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd_args;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

/*-----ast.c-----*/

/*-----ast_cmd.c-----*/

t_cmd	*new_cmd(char **cmd_args, t_redir *redir);
void	add_cmd(char **cmd_args, t_redir *redir, t_cmd **root);

/*-----ast_redir.c-----*/

t_redir	*new_redir(t_redir_type type, char *file, bool ex_here);
void	add_redir(t_redir_type type, char *file, bool ex_here, t_redir **head);
void	free_redir_list(t_redir	*head);

/*-----ast_expand.c-----*/

char	*expand_variable(char *var_name, char **envp);

#endif
