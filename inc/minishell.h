/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:23:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 18:07:43 by adecauch         ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "envp.h"
# include "signals.h"
# include "builtin.h"
# include "tokenizer.h"
# include "ast.h"
# include "struct_ms.h"
# include "debug.h"
# include "exec.h"

/*-----minishell.c-----*/

int		process_input(t_shell *shell);
int		minishell(t_shell shell);

#endif
