/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:00:55 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/12 00:31:38 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC,
	T_INVALID
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	bool			expand;
	struct s_token	*next;
}	t_token;

/*-----token.c-----*/

t_token	*new_token(char *str, t_token_type type, bool expand);
void	add_token(char *str, t_token_type type, bool expand, t_token **head);
void	free_token_list(t_token	*head);

/*-----tokenizer-----*/ 

/*-----tokenizer_utility-----*/

bool	check_unclosed_quotes(char *input);

#endif
