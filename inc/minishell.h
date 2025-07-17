/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:23:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/17 14:16:41 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
//# define RL_NO_COMPAT

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"
# include "signals.h"
# include "tokenizer.h"
# include "ast.h"
# include "debug.h"

typedef struct s_shell
{
	char	*input;
	char	**envp;
	t_token	*head;
	t_cmd	*root;
	int		exit_status;
}	t_shell;

char	**copy_envp(char **envp);
void	process_input(t_shell shell);
int		minishell(t_shell shell);

#endif
