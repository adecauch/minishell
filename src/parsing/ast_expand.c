/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:21:12 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/17 16:21:18 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

char	*get_env_value(char *name, char **envp, int last_status)
{
	int		i;
	size_t	len;

	if (name[0] == '?' && name[1] == '\0')
		return (ft_itoa(last_status));
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

bool	is_valid_var_char(char c, int pos)
{
	if (pos == 0)
		return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| c == '_' || c == '?');
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_');
}

char	*expand_str(char *str, char **envp, int last_status)
{
	char	*res;
	int		i;
	int		start;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (!str[i] || !is_valid_var_char(str[i], 0))
				res = join_and_free(res, ft_strdup("$"));
			start = i;
			while (str[i] && is_valid_var_char(str[i], i - start))
				i++;
			res = join_and_free(res,
					get_env_value(ft_substr(str, start, i - start),
						envp, last_status));
		}
		else
			res = join_and_free(res, ft_substr(str, i++, 1));
	}
	return (res);
}
/*
int	main(int argc, char **argv, char **envp)
{
	printf("%s\n", expand_str("$USER test $USER $& $?", envp, 0));
}
cc src/parsing/ast_expand.c src/libft/ft_strdup.c src/libft/ft_substr.c
src/libft/ft_strncmp.c src/libft/ft_strjoin.c src/libft/ft_strlen.c
src/libft/ft_itoa.c src/libft/ft_strlcpy.c
*/
