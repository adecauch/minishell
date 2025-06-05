/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:40:18 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/05 02:27:36 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenizer(char *line)
{
	t_token	*head_token;
	int		i;

	i = 0;
	head_token = NULL;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
			add(&i, &head_token, T_PIPE, "|");
		else if (line[i] == '>' && line[i + 1] == '>')
			add(&i, &head_token, T_APPEND, ">>");
		else if (line[i] == '>')
			add(&i, &head_token, T_OUT, ">");
		else if (line[i] == '<' && line[i + 1] == '<')
			add(&i, &head_token, T_HEREDOC, "<<");
		else if (line[i] == '<')
			add(&i, &head_token, T_IN, "<");
		else if (line[i] == '\'' || line[i] == '"')
			add_token(&head_token, T_WORD, parse_quote(line, &i));
		else
			add_token(&head_token, T_WORD, parse_word(line, &i));
	}
	return (head_token);
}
/*
int	main(void)
{
	t_token *head_token = tokenizer("cat file1 > file2");

	while (head_token)
	{
		printf("%s\n", head_token->str);
		head_token = head_token->next;
	}
		free_token_list(head_token);
}
*/
//ccf src/tokenizer/tokenizer.c src/tokenizer/tokenizer_utility.c src/tokenizer/token.c src/libft/ft_isspace.c src/libft/ft_substr.c src/libft/ft_strlen.c src/libft/ft_strdup.c -o tokenizer
