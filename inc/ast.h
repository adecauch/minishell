/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:10 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 17:58:12 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_rtype
{
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_rtype;

typedef struct s_redir
{
	t_rtype			type;
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

t_cmd	*make_ast(t_token *head, char **envp, int last_status);
t_redir	*extract_redir(t_token *head, char **envp, int last_status);
char	**extract_cmd_args(t_token *head, char **envp, int last_status);

/*-----ast_cmd.c-----*/

t_cmd	*new_cmd(char **cmd_args, t_redir *redir);
void	add_cmd(char **cmd_args, t_redir *redir, t_cmd **root);
void	free_cmd_list(t_cmd *head);

/*-----ast_redir.c-----*/

t_redir	*new_redir(t_rtype type, char *file, bool ex_here);
void	add_redir(t_rtype type, char *file, bool ex_here, t_redir **head);
void	free_redir_list(t_redir	*head);

/*-----ast_expand.c-----*/

char	*join_and_free(char *s1, char *s2);
char	*get_env_value(char *name, char **envp, int last_status);
bool	is_valid_var_char(char c, int pos);
char	*expand_str(char *str, char **envp, int last_status);

/*-----ast_utility.c-----*/

int		count_args(t_token *head);
t_rtype	ttype_to_rtype(t_token_type type);
void	free_str_array(char **arr);

#endif
