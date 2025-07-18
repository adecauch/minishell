/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:18:10 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 17:49:55 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*make_ast(t_token *head, char **envp, int last_status)
{
	t_cmd	*root;
	char	**cmd_args;
	t_redir	*redir;

	root = NULL;
	while (has_remaining_tokens(head))
	{
		redir = extract_redir(head, envp, last_status);
		cmd_args = extract_cmd_args(head, envp, last_status);
		add_cmd(cmd_args, redir, &root);
		while (head && head->type != T_PIPE)
			head = head->next;
		if (head && head->type == T_PIPE)
		{
			head->type = T_SKIP;
			head = head->next;
		}
	}
	return (root);
}

char	**extract_cmd_args(t_token *head, char **envp, int last_status)
{
	char	**cmd_args;
	int		i;
	int		count;

	i = 0;
	count = count_args(head);
	if (!count)
		return (NULL);
	cmd_args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_args)
		return (NULL);
	while (head && head->type != T_PIPE)
	{
		if (isword_type(head->type))
		{
			if (head->type == T_DQWORD || head->type == T_WORD)
				cmd_args[i++] = expand_str(head->str, envp, last_status);
			else
				cmd_args[i++] = ft_strdup(head->str);
			head->type = T_SKIP;
		}
		head = head->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
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
