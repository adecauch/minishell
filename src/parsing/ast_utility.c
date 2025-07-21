/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:46:59 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/19 17:22:36 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_rtype	ttype_to_rtype(t_token_type type)
{
	if (type == T_IN)
		return (IN);
	if (type == T_OUT)
		return (OUT);
	if (type == T_APPEND)
		return (APPEND);
	return (HEREDOC);
}

void	free_str_array(char **arr)
{
	char	**tmp;

	if (!arr)
		return ;
	tmp = arr;
	while (*tmp)
		free(*tmp++);
	free(arr);
}

bool	is_builtin(char **cmd_args)
{
	int	len;

	if (!cmd_args || !cmd_args[0])
		return (0);
	len = ft_strlen(cmd_args[0]);
	if (!ft_strncmp(cmd_args[0], "echo", len) && len == 4)
		return (1);
	if (!ft_strncmp(cmd_args[0], "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(cmd_args[0], "pwd", len) && len == 3)
		return (1);
	if (!ft_strncmp(cmd_args[0], "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(cmd_args[0], "unset", len) && len == 5)
		return (1);
	if (!ft_strncmp(cmd_args[0], "env", len) && len == 3)
		return (1);
	if (!ft_strncmp(cmd_args[0], "exit", len) && len == 4)
		return (1);
	return (0);
}

void	check_builtin(t_cmd *root)
{
	while (root)
	{
		root->is_builtin = is_builtin(root->cmd_args);
		root = root->next;
	}
}
