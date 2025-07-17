/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:00:55 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/17 11:52:51 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_token_type
{
	T_WORD,
	T_SQWORD,
	T_DQWORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC,
	T_INVALID,
	T_SKIP
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/*-----token.c-----*/

t_token	*new_token(char *str, t_token_type type);
void	add_token(char *str, t_token_type type, t_token **head);
void	add_redir_token(char *str, t_token_type type, t_token **head, int *i);
void	free_token_list(t_token	*head);

/*-----tokenizer.c-----*/

bool	check_unclosed_quotes(char *input);
void	handle_token(char *input, int *i, t_token **head);
void	validate_token_list(t_token *head);
bool	check_token_list(t_token *head);
t_token	*tokenizer(char *input);

/*-----tokenizer_utility_one.c-----*/

char	*parse_word(char *input, int *i);
char	*parse_squotes(char *input, int *i);
char	*parse_dquotes(char *input, int *i);
bool	contains_invalid_char(char *str);

/*-----tokenizer_utility_two.c-----*/

bool	isredir(char c);
bool	isredir_type(t_token_type type);
bool	isword_type(t_token_type type);
bool	error_msg(char *msg);

#endif
