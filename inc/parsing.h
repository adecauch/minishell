/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 04:00:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/11 04:00:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_REDIRECTION
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	char			**args;
	char			*redir_file;
	int				redir_fd;
	t_ast_type		redir_type;
	struct s_ast	*next;
}	t_ast;

/*-----parsing.c-----*/
t_ast	*parse(t_token *tokens);
t_ast	*parse_command(t_token **tokens);

/*-----parsing_utils.c-----*/
void	add_to_list(t_ast **head, t_ast *new_node);
t_token	*skip_token(t_token **tokens);
int		is_redirection(t_token_type type);
t_ast	*create_redirection_node(t_token **tokens);

/*-----ast.c-----*/
t_ast	*ast_new(t_ast_type type);
void	ast_add_arg(t_ast *node, char *arg);
void	free_ast(t_ast *root);
void	ast_print(t_ast *root, int depth);

#endif
