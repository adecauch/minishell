/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_ms.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:04:31 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 18:06:49 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MS_H
# define STRUCT_MS_H

typedef struct s_shell
{
	char	*input;
	char	**envp;
	t_token	*head;
	t_cmd	*root;
	int		last_status;
	bool	exit;
}	t_shell;

#endif
