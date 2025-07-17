/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:18:10 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/17 22:37:59 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*make_ast(t_token *head, char **envp, int last_status)
{
	
}

t_redir_type	ttype_to_rtype(t_token_type type)
{
	if (type == T_IN)
		return (IN);
	if (type == T_OUT)
		return (OUT);
	if (type == T_APPEND)
		return (APPEND);
	return (HEREDOC);
}

t_redir	*extract_redir(t_token *head, char **envp, int last_status)
{
	t_redir			*redir;
	bool			ex_here;
	char			*file;

	redir = NULL;
	while (head && head->type != T_PIPE)
	{
		if (isredir_type(head->type))
		{
			ex_here = (ttype_to_rtype(head->type) == HEREDOC
					&& head->next->type != T_SQWORD);
			if (head->next->type == T_SQWORD)
				file = head->next->str;
			else
				file = expand_str(head->next->str, envp, last_status);
			add_redir(ttype_to_rtype(head->type), file, ex_here, &redir);
			if (head->next->type != T_SQWORD)
				free(file);
			head->type = T_SKIP;
			head = head->next;
			head->type = T_SKIP;
		}
		head = head->next;
	}
	return (redir);
}
