/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:27:29 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/10 19:54:51 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*-----echo.c-----*/

int		bi_echo(char **cmd_args);

/*-----cd.c-----*/

int		bi_cd(char **cmd_args, char ***envp);

/*-----pwd.c-----*/

int		bi_pwd(char **cmd_args);

/*-----export.c-----*/

int		bi_export(char **cmd_args, char ***envp);

/*-----print_export.c-----*/

void	print_export(char **envp);

/*-----unset.c-----*/



/*-----env.c-----*/

int	bi_env(char **cmd_args, char **envp);

/*-----exit.c-----*/

int	bi_exit(char **cmd_args, int *last_status)

#endif
