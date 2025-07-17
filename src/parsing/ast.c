/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:18:10 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/17 23:46:48 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*make_ast(t_token *head, char **envp, int last_status)
{
	t_cmd	*root;
	t_cmd	*cmd;
	char	**cmd_args;
	t_redir	*redir;
	t_token	*curr;

	root = NULL;
	curr = head;
	while (has_remaining_tokens(curr))
	{
		redir = extract_redir(curr, envp, last_status);
		cmd_args = extract_cmd_args(curr, envp, last_status);
		add_cmd(cmd_args, redir, &root);
		while (curr && curr->type != T_PIPE)
			curr = curr->next;
		if (curr && curr->type == T_PIPE)
		{
			curr->type = T_SKIP;
			curr = curr->next;
		}
	}
	return (root);
}

int	count_args(t_token *head)
{
	int	count;

	count = 0;
	while (head && head->type != T_PIPE)
	{
		if (isword_type(head->type))
			count++;
		head = head->next;
	}
	return (count);
}

char	**extract_cmd_args(t_token *head, char **envp, int last_status)
{
	char	**args;
	int		i;
	int		count;

	i = 0;
	count = count_args(head);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	while (head && head->type != T_PIPE)
	{
		if (isword_type(head->type))
		{
			if (head->type == T_DQWORD || head->type == T_WORD)
				args[i++] = expand_str(head->str, envp, last_status);
			else
				args[i++] = ft_strdup(head->str);
			head->type = T_SKIP;
		}
		head = head->next;
	}
	args[i] = NULL;
	return (args);
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
