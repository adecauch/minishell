/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:22:39 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 17:50:44 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char **cmd_args, t_redir *redir)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_args = cmd_args;
	cmd->redir = redir;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(char **cmd_args, t_redir *redir, t_cmd **root)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = new_cmd(cmd_args, redir);
	if (!cmd)
		return ;
	if (!*root)
		*root = cmd;
	else
	{
		tmp = *root;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->cmd_args)
			free_str_array(head->cmd_args);
		if (head->redir)
			free_redir_list(head->redir);
		free(head);
		head = tmp;
	}
}
