/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:23:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 03:57:55 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <limits.h>
# include "libft.h"
# include "envp.h"
# include "signals.h"
# include "builtin.h"
# include "tokenizer.h"
# include "ast.h"
# include "debug.h"

typedef struct s_shell
{
	char	*input;
	char	**envp;
	t_token	*head;
	t_cmd	*root;
	int		last_status;
}	t_shell;

# include "exec.h"

int		process_input(t_shell shell);
int		minishell(t_shell shell);

#endif
