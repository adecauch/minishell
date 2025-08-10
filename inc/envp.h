/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:21:33 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/10 01:56:45 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

/*-----envp.c-----*/

char	**copy_envp(char **envp);
int		set_env_var(char ***envp, char *name, char *value);
int		unset_env_var(char ***envp, char *name);

/*-----envp_utility-----*/

int		count_env_vars(char **envp);
int		find_env_var(char **envp, char *name);

/*-----set_env_var-----*/

char	*create_env_entry(char *name, char *value);
char	**allocate_new_envp(char **envp, int count);
int		update_existing_var(char ***envp, int index, char *new_entry);
int		add_new_var(char ***envp, char *new_entry);

/*-----unset_env_var_utility.c-----*/

char	**create_reduced_envp(char **envp, int count, int skip_index);
void	remove_env_entry(char ***envp, int index);

#endif
