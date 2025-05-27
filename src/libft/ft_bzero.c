/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:50:47 by adecauch          #+#    #+#             */
/*   Updated: 2024/11/18 19:25:32 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
}
