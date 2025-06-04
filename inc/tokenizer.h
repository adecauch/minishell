/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:37:54 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/05 01:39:16 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*-----token.c-----*/

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_token	*new_token(t_token_type type, char *str);
void	add_token(t_token **head_token, t_token_type type, char *str);
void	free_token_list(t_token *head_token);

/*----tokenizer_utility.c-----*/
int		isspecial(char c);
char	*parse_word(char *line, int *i);
char	*parse_quote(char *line);
void	add(int *i, t_token **head_token, t_token_type type, char *str);

/*-----tokenizer.c-----*/

t_token	*tokenizer(char *line);

#endif
