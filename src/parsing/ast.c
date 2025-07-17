/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:18:10 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/17 15:30:10 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*make_ast(t_token *head, char **envp)
{
	
}

t_redir	*extract_redir(t_token *head, char **envp)
{
	t_redir	*redir;

	redir == NULL;
	while (head && head->type != T_PIPE)
	{
		if (isredir_type(head->type))
		{
			if (head->type == T_IN)
			{
				if (head->next->type ==)
			}
		}

		head = head->next;
	}
}
