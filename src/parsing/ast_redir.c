/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:45:50 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 17:27:28 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*new_redir(t_rtype type, char *file, bool ex_here)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->ex_here = ex_here;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_rtype type, char *file, bool ex_here, t_redir **head)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = new_redir(type, file, ex_here);
	if (!redir)
		return ;
	if (!*head)
		*head = redir;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

void	free_redir_list(t_redir	*head)
{
	t_redir	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->file);
		free(head);
		head = tmp;
	}
}
