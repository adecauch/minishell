/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
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
	AST_SEQUENCE,
	AST_PIPELINE,
	AST_SIMPLE_COMMAND,
	AST_REDIRECTION
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	char			*command;
	char			**args;
	char			*redir_file;
	int				redir_fd;
	t_ast_type		redir_type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

/*-----parsing.c-----*/
t_ast	*parse(t_token *tokens);
t_ast	*parse_sequence(t_token **tokens);
t_ast	*parse_pipeline(t_token **tokens);
t_ast	*parse_simple_command(t_token **tokens);
t_ast	*parse_redirection(t_token **tokens);

/*-----ast.c-----*/
t_ast	*ast_new(t_ast_type type);
void	ast_add_arg(t_ast *node, char *arg);
void	free_ast(t_ast *root);
void	ast_print(t_ast *root, int depth);

#endif
