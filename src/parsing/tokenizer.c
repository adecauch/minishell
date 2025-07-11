/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:53:45 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/12 00:35:13 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	handle_token(char *input, int *i, t_token **head)
{
	if (ft_isspace(input[*i]))
		(*i)++;
	else if (input[*i] == '|')
	{
		add_token("|", T_PIPE, false, head);
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		add_token("<", T_IN, false, head);
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		add_token(">", T_OUT, false, head);
		(*i)++;
	}
	else if (input[*i] == '<' && input[*i+1] == '<')
	{
		add_token("<<", T_HEREDOC, false ,head);
		(*i) += 2;
	}
	else if (input[*i] == '>' && input[*i+1] == '>')
	{
		add_token(">>", T_APPEND, false, head);
		(*i) += 2;
	}
}

t_token	*tokenizer(char *input)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while(input[i])
		handle_token(input, &i, &head);
	return (head);
}
